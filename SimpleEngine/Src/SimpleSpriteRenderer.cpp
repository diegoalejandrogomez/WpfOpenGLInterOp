#include "stdafx.h"
#include "SimpleSpriteRenderer.h"
#include "SimpleEngine.h"
#include <algorithm>
#include <glm\gtx\transform.hpp>

SimpleSpriteRenderer::SimpleSpriteRenderer() {

	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();
	//All the sprites use the same geometry
	_mesh = render->GetUnitaryQuad();
	_shader = render->GetProgram("VertexSprite");
	_cam = SimpleEngine::Instance()->GetScene()->GetCamera();

	_rectOffset = glm::vec2(0.0f);
	_rectSize = glm::vec2(0.0f);
}

void SimpleSpriteRenderer::SetRect(glm::vec2 offset, glm::vec2 size) {
	_rectOffset = offset;
	_rectSize = size;
	//Resize accordingly
	_size = _rectSize;
}

SimpleSpriteRenderer::~SimpleSpriteRenderer() {

	delete _mesh;

}

void SimpleSpriteRenderer::SetAsTexture(std::string && name) {
	
	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();
	_tex = render->GetTexture(name);
	_rectOffset = { 0,0 };
	_rectSize = { _tex->GetWidth(), _tex->GetHeight() };
	//Set sprite size using texture resolution
	_size = _rectSize;
}

void SimpleSpriteRenderer::SetAsTextureRect(std::string && name, glm::vec2 offset, glm::vec2 size) {
	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();
	_tex = render->GetTexture(name);
	SetRect(offset, size);
}


void SimpleSpriteRenderer::Advance(float dt) {



}

void SimpleSpriteRenderer::Render(float dt) {
		
	_shader->Bind();
		
	//Bad way of querying uniforms
	GLuint modelLoc = _shader->GetLocationFor( "modelMatrix");

	//Not efficient at all, but easier to read for now
	
	//glm::mat4 model = glm::translate(_position) * glm::rotate(_orientation, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::vec3(_size.x, _size.y, 1.0f ));
	glm::mat4 model = glm::scale(glm::vec3(_size.x, _size.y, 1.0f));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

	GLuint viewProjectionLoc = _shader->GetLocationFor("viewProjectionMatrix");
	glUniformMatrix4fv(viewProjectionLoc, 1, GL_FALSE, &_cam->GetViewProjection()[0][0]);

	GLuint uvOffsetLoc = _shader->GetLocationFor("uvOffset");
	glUniform2f(uvOffsetLoc,_rectOffset[0] / (float)_tex->GetWidth(),
							_rectOffset[1] / (float)_tex->GetHeight());


	GLuint uvSizeLoc = _shader->GetLocationFor("uvSize");
	glUniform2f(uvSizeLoc, _rectSize[0] / (float)_tex->GetWidth(),
							_rectSize[1] / (float)_tex->GetHeight());

	GLuint sizeRatioLoc = _shader->GetLocationFor("sizeRatio");
	glUniform2f(sizeRatioLoc,	_tex->GetWidthRatio(),
								_tex->GetHeightRatio());


	GLuint textureLoc = _shader->GetLocationFor("texSampler");
	glUniform1i(textureLoc, 0); //Texture unit 0 is for base images.

	//end uniform query

	_tex->BindTo(0);

	_mesh->Bind();
	_mesh->Draw();
	_mesh->Unbind();


}


