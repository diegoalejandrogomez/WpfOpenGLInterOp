#pragma once
#include <glm\glm.hpp>
#include "SimpleAABB.h"
#include <algorithm>
#include "SimpleConfiguration.h"


class SIMPLE_API SimpleCamera2D {
	
public:

	SimpleCamera2D();
	~SimpleCamera2D();

	void SetPosition(float x, float y);
	void SetZoom(float zoom);
	//Offsets the zoom to have a value of 1 on world size width
	void SetMaxVisibleArea(SimpleAABB area);
	void Move(float dx, float dy);
	void DeltaZoom(float dz);
	void ZoomToArea(SimpleAABB area);
	void SetViewportSize(float w, float h);
	
	glm::mat4 &GetViewProjection() {return _viewProjection;}
	glm::mat4 &GetView() {return _view;}
	glm::mat4 &GetProjection() {return _projection;}
	float GetWidth() { return _size.x / _zoom; };
	float GetHeight() { return _size.y / _zoom; };
	float GetZoom() { return _zoom; }
	float GetMaxZoom() { return std::min(_size.x, _size.y); };

	glm::vec2 ScreenToWorld(glm::vec2 viewPos);
	glm::vec2 ViewportToWorld(glm::vec2 viewPos);
	
	glm::vec2 WorldToScreen(glm::vec2 worldPos);
	glm::vec2 WorldToViewport(glm::vec2 worldPos);
	
private:
	
	void _UpdateTransform();
	
	//Transform matrices
	glm::mat4 _view;
	glm::mat4 _projection;
	glm::mat4 _viewProjection;
	//Camera properties
	glm::vec3 _position;
	glm::vec2 _size;
	float _zoom;
	float _aspectRatio;
	SimpleAABB _restrictedArea;
};