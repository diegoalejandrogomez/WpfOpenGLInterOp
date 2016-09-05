#include "stdafx.h"
#include "SimpleDebugObject.h"
#include "SimpleEngine.h"
#include <algorithm>

SimpleDebugObject::SimpleDebugObject() {

	VertexColorFormat2D * vertices;
	unsigned int verticesSize;
	unsigned int* indices;
	unsigned int indicesSize;
	unsigned int size = 0;

	//Save reference to the used shader
	auto renderer = SimpleEngine::Instance()->GetRenderer();
	auto resources = SimpleEngine::Instance()->GetResourceManager();
	_shader = resources->GetProgram("VertexColor");
	_cam = SimpleEngine::Instance()->GetScene()->GetCamera();
	
	//Generate geometry
	_GeneratePositionAndColor(vertices, verticesSize, indices ,indicesSize);
	_vertexCount = verticesSize;
	_indexCount = indicesSize;
		
	//Generate vertex array VAO
	GL_CHECK(glGenVertexArrays(1, &_vao));

	//Bind VAO
	GL_CHECK(glBindVertexArray(_vao));
	
	//Generate buffers
	GL_CHECK(glGenBuffers(2, _vbos));

	//Bind vertex buffer
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _vbos[0]));

	//Upload data to buffer
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(VertexColorFormat2D)*verticesSize,vertices ,GL_STATIC_DRAW));
		
	//Configure vertex channels to currently bounded vao at position 0
	GL_CHECK(glBindVertexBuffer(0, _vbos[0], 0 , sizeof(VertexColorFormat2D)));
	
	//Configure vertex format for index 0 
	GL_CHECK(glVertexAttribFormat(0, 2, GL_FLOAT, GL_FALSE, offsetof(VertexColorFormat2D, pos)));
	GL_CHECK(glVertexAttribBinding(0, 0));
	GL_CHECK(glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, offsetof(VertexColorFormat2D, color)));
	GL_CHECK(glVertexAttribBinding(1, 0));
	//Enable vertex attributes 0 and 1 for position and colour
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glEnableVertexAttribArray(1));
		
	//Bind the index buffer
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[1]));

	//Upload indices
	GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesSize, indices, GL_STATIC_DRAW));


	//unbind vao
	GL_CHECK(glBindVertexArray(0));

	//Delete the CPU buffers
	delete[] vertices;
	delete[] indices;

	
		
}

SimpleDebugObject::~SimpleDebugObject() {

	glDeleteBuffers(2, _vbos);
	glDeleteVertexArrays(1, &_vao);

}

void SimpleDebugObject::_GeneratePositionAndColor(	VertexColorFormat2D* &vertexs, 
													unsigned int &verticesSize, 
													unsigned int* &indices, 
													unsigned int &indicesSize) {

	
	float halfSize = std::min(_cam->GetWidth(), _cam->GetHeight()) * 0.4f;
	verticesSize = 4;
	vertexs = new VertexColorFormat2D[12];
	indices = new unsigned int[6];
	indicesSize = 6;
	

	vertexs[0].pos[0] = -halfSize; vertexs[0].pos[1] = -halfSize;								// Bottom left corner  
	vertexs[0].color[0] = 1.0; vertexs[0].color[1] = 1.0; vertexs[0].color[2] = 1.0; // Bottom left corner  
	
	vertexs[1].pos[0] = -halfSize; vertexs[1].pos[1] = halfSize; // Top left corner  
	vertexs[1].color[0] = 1.0; vertexs[1].color[1] = 0.0; vertexs[1].color[2] = 0.0; // Top left corner  

	vertexs[2].pos[0] = halfSize; vertexs[2].pos[1] = halfSize;	// Top Right corner  
	vertexs[2].color[0] = 0.0; vertexs[2].color[1] = 1.0; vertexs[2].color[2] = 0.0; // Top Right corner  

	vertexs[3].pos[0] = halfSize; vertexs[3].pos[1] = -halfSize;	// Bottom right corner  
	vertexs[3].color[0] = 0.0; vertexs[3].color[1] = 0.0; vertexs[3].color[2] = 1.0; // Bottom right corner  

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
}
void SimpleDebugObject::Advance(float dt) {



}

void SimpleDebugObject::Render(float dt) {

	
	_shader->Bind();

	//Bad way of querying uniforms
	GLuint modelLocation = _shader->GetLocationFor("modelMatrix");
	glUniformMatrix4fv(modelLocation,1,GL_FALSE, &glm::mat4(1.0)[0][0]);

	GLuint viewProjectionLocation = _shader->GetLocationFor("viewProjectionMatrix");
	
	glUniformMatrix4fv(viewProjectionLocation, 1, GL_FALSE, &_cam->GetViewProjection()[0][0]);
	//end uniform query
	
	GL_CHECK(glBindVertexArray(_vao)); // Bind our Vertex Array Object  

	GL_CHECK(glDrawElements(GL_TRIANGLES, _indexCount , GL_UNSIGNED_INT, 0)); // Draw our square  

	glBindVertexArray(0); // Unbind our Vertex Array Object  


}


