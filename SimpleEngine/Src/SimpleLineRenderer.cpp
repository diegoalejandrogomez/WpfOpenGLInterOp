#include "stdafx.h"
#include "SimpleLineRenderer.h"
#include <glm\gtx\transform.hpp>

SimpleLineRenderer::SimpleLineRenderer() {

	SimpleRenderer* render = SimpleEngine::Instance()->GetRenderer();
	//All the sprites use the same geometry
	_mesh = new SimpleMesh<VertexColorFormat2D>(false);
	_shader = render->GetProgram("VertexColor");
	_cam = SimpleEngine::Instance()->GetScene()->GetCamera();
	
}

void SimpleLineRenderer::Flush() {
	
	_mesh->SetVertices(&_vertices[0], _vertices.size(), GL_STATIC_DRAW);
	
}

void SimpleLineRenderer::Advance(float dt) {
}

void SimpleLineRenderer::Render(float dt) {

	_shader->Bind();

	//Bad way of querying uniforms
	GLuint modelLoc = _shader->GetLocationFor("modelMatrix");

	//Not efficient at all, but easier to read for now

	glm::mat4 model = glm::mat4(1.0f); //All the lines are in world space


	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

	GLuint viewProjectionLoc = _shader->GetLocationFor("viewProjectionMatrix");
	glUniformMatrix4fv(viewProjectionLoc, 1, GL_FALSE, &_cam->GetViewProjection()[0][0]);

	_mesh->Bind();
	_mesh->DrawUnindexed(GL_LINES);
	_mesh->Unbind();

}
SimpleLineRenderer::~SimpleLineRenderer() {

	delete _mesh;
}


void SimpleLineRenderer::AddLine(glm::vec2 from, glm::vec2 to, glm::vec3 color) {
	
	VertexColorFormat2D v;
	v.pos[0] = from.x;
	v.pos[1] = from.y;
	v.color[0] = color.r;
	v.color[1] = color.g;
	v.color[2] = color.b;
	_vertices.push_back(v);

	v.pos[0] = to.x;
	v.pos[1] = to.y;
	v.color[0] = color.r;
	v.color[1] = color.g;
	v.color[2] = color.b;
	_vertices.push_back(v);
	
}
void SimpleLineRenderer::ClearLines() {
	_vertices.clear();
}

