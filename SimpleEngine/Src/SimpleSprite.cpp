#include "stdafx.h"
#include "SimpleSprite.h"
#include "SimpleEngine.h"
#include <algorithm>

SimpleSprite::SimpleSprite() {

	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();
	//All the sprites use the same geometry
	_mesh = render->GetUnitaryQuad();
	_shader = render->GetProgram("VertexSprite");

	_offset = glm::vec2(0.0f);
	_size = glm::vec2(0.0f);
}

SimpleSprite::~SimpleSprite() {

	delete _mesh;

}

void SimpleSprite::SetAsTexture(std::string && name) {
	
	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();
	_tex = render->GetTexture(name);
	_offset = { 0,0 };
	_size = { _tex->GetWidth(), _tex->GetHeight() };
}

void SimpleSprite::SetAsTextureRect(std::string && name, glm::vec2 offset, glm::vec2 size) {
	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();
	_tex = render->GetTexture(name);
	_offset = offset;
	_size = size;
}


void SimpleSprite::Advance(float dt) {



}

void SimpleSprite::Render(float dt) {
		
	_shader->Bind();
		
	//Bad way of querying uniforms
	GLuint modelLocation = _shader->GetLocationFor( "modelMatrix");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &glm::mat4(1.0)[0][0]);

	GLuint viewProjectionLocation = _shader->GetLocationFor("viewProjectionMatrix");

	glUniformMatrix4fv(viewProjectionLocation, 1, GL_FALSE, &_cam->GetViewProjection()[0][0]);
	//end uniform query

	_mesh->Bind();
	_mesh->Draw();
	_mesh->Unbind();


}


