#include "stdafx.h"
#include "SimpleCamera2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include "SimpleDispatcher.h"
#include "SimpleEngine.h"

SimpleCamera2D::SimpleCamera2D() {
	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();

	_view = glm::mat4(1.0f);
	_projection = glm::mat4(1.0f);
	_viewProjection = glm::mat4(1.0);
	_position = glm::vec3(0.0f);
	_size = { render->GetWidth(), render->GetHeight() };
	_zoom = 0.0f;
	_restrictedArea.position = { 0.0f ,0.0f,0.0f };
	_restrictedArea.size = _size;

	SimpleDispatcher::Instance()->AddListener(WindowResizeEvent::descriptor, {
		this,
		[this](const SimpleEvent& evt) {
		const WindowResizeEvent &res = static_cast<const WindowResizeEvent&>(evt);
		this->SetViewportSize(res.width,res.height);
		}
	});
	
	_UpdateTransform();
}


SimpleCamera2D::~SimpleCamera2D() {

	SimpleDispatcher::Instance()->RemoveListener(WindowResizeEvent::descriptor, this);

}


void SimpleCamera2D::_UpdateTransform() {
	
	

	_zoom = std::max(1e-3f, _zoom);

	//Compute zoom offset due to desired visible size
	float _offsetX = _size.x / _restrictedArea.size.x;
	float _offsetY = _size.y / _restrictedArea.size.y;
	float _zoomOffset = std::min(_offsetX, _offsetY);
	//This value should be >= 1 
	float finalZoom = std::max(1.01f,_zoomOffset + _zoom);

	float halfWidth	= _size.x *0.5f / finalZoom;
	float halfHeight= _size.y * 0.5f / finalZoom;
	
	float restrictedLeft = (_restrictedArea.position.x - _restrictedArea.size.x * 0.5f);
	float restrictedRight = (_restrictedArea.position.x + _restrictedArea.size.x *0.5f);

		//Clamp position to match restrictions taking into account the aspect ratio
	float leftOverlap;
	float rightOverlap;
	float sign = 1.0f;
	if (halfWidth <= _restrictedArea.size.x * 0.5f) {
		leftOverlap = (_position.x - halfWidth) - restrictedLeft;
		rightOverlap = restrictedRight - (_position.x + halfWidth);
		sign = 1.0f;
		
	}
	else {
		leftOverlap = restrictedLeft - (_position.x - halfWidth);
		rightOverlap = (_position.x + halfWidth) - restrictedRight;
		sign = -1.0f;
	}

	
	if (leftOverlap < 0.0f)
		_position.x -= sign * leftOverlap;
	if (rightOverlap < 0.0f)
		_position.x += sign * rightOverlap;


	float restrictedTop = (_restrictedArea.position.y - _restrictedArea.size.y * 0.5f);
	float restrictedBottom = (_restrictedArea.position.y + _restrictedArea.size.y * 0.5f);

	float topOverlap;
	float bottomOverlap;
	if (halfHeight <= _restrictedArea.size.y * 0.5f) {
		topOverlap = (_position.y - halfHeight) - restrictedTop;
		bottomOverlap = restrictedBottom - (_position.y + halfHeight);
		sign = 1.0f;
		
	}
	else {
		topOverlap = restrictedTop - (_position.y - halfHeight);
		bottomOverlap = (_position.y + halfHeight) - restrictedBottom;
		sign = -1.0f;
	}
	
	if (topOverlap < 0.0f)
		_position.y -= sign * topOverlap;
	if (bottomOverlap < 0.0f)
		_position.y += sign * bottomOverlap;
	
	
	_view = glm::translate(glm::mat4(1.0f), -_position);
	_projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.0f, 1.0f);
	_viewProjection = _projection * _view;

}
void SimpleCamera2D::SetPosition(float x, float y) {
	_position.x = x;
	_position.y = y;
	_UpdateTransform();
}

void SimpleCamera2D::SetZoom(float zoom) {
	_zoom = zoom;
	_UpdateTransform();
}


void SimpleCamera2D::DeltaZoom(float dz) {
	_zoom += dz;
	_UpdateTransform();
}

void SimpleCamera2D::Move(float dx, float dy) {
	_position.x += dx;
	_position.y += dy;

	_UpdateTransform();
}
void SimpleCamera2D::SetViewportSize(float w, float h) {

	_aspectRatio = w / h;

	//Readjust zoom
	//_zoom *= std::max(w / _size.x, h / _size.y);
	_size.x = w;
	_size.y = h;
		
	_UpdateTransform();
}


void SimpleCamera2D::SetMaxVisibleArea(SimpleAABB area){
	_restrictedArea = area;
	_UpdateTransform();
}

void SimpleCamera2D::ZoomToArea(SimpleAABB area) {
	_position = area.position;

	//Change zoom accordingly maintaining aspect ratio
	glm::vec2 zoomFactors =  _size / area.size;
	SetZoom(std::min(zoomFactors.x, zoomFactors.y));
}

glm::vec2 SimpleCamera2D::ScreenToWorld(glm::vec2 viewPos) {
	viewPos.y = _size.y - viewPos.y;
	glm::vec2 normalized = viewPos / _size * 2.0f - 1.0f;
	//to normalized [-1:1]
	glm::vec4 worldPos = glm::inverse(_viewProjection) * glm::vec4{ normalized.x, normalized.y, 0.0f, 1.0f };
	//-> to world space
	return{ worldPos.x, worldPos.y };
}

glm::vec2 SimpleCamera2D::ViewportToWorld(glm::vec2 viewPos) {
	glm::vec2 normalized = viewPos / _size * 2.0f - 1.0f;
	//to normalized [-1:1]
	glm::vec4 worldPos = glm::inverse(_viewProjection) * glm::vec4{ normalized.x, normalized.y, 0.0f, 1.0f };
	//-> to world space
	return{ worldPos.x, worldPos.y };
}


glm::vec2 SimpleCamera2D::WorldToScreen(glm::vec2 worldPos) {
	
	glm::vec4 normalized = _viewProjection *glm::vec4{ worldPos.x, worldPos.y, 0.0f, 1.0f };
	normalized = (normalized + 1.0f) * 0.5f;
	return{ normalized.x * _size.x ,  _size.y - normalized.y * _size.y };

}
glm::vec2 SimpleCamera2D::WorldToViewport(glm::vec2 worldPos) {

	glm::vec4 normalized = _viewProjection *glm::vec4{ worldPos.x, worldPos.y, 0.0f, 1.0f };
	normalized = (normalized + 1.0f) * 0.5f;
	return{ normalized.x * _size.x , normalized.y * _size.y };
}