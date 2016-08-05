#pragma once
#include "stdafx.h"

template <class VERTEX_TYPE>
class SimpleMesh {

public:

	//Initialize the buffers without data
	SimpleMesh() {
		//Generate vertex array VAO
		GL_CHECK(glGenVertexArrays(1, &_vao));

		//Generate buffers
		GL_CHECK(glGenBuffers(2, _vbos));

		//Bind VAO
		GL_CHECK(glBindVertexArray(_vao));

		//Bind vertex buffer
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _vbos[0]));

		//Configure vertex channels to currently bounded vao at position 0
		GL_CHECK(glBindVertexBuffer(0, _vbos[0], 0, sizeof(VERTEX_TYPE)));
		
		//Configure vertex format
		VERTEX_TYPE::Bind(0);

		//Bind the index buffer
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[1]));

		//unbind vao
		GL_CHECK(glBindVertexArray(0));
	}

	~SimpleMesh() {
		glDeleteBuffers(2, _vbos);
		glDeleteVertexArrays(1, &_vao);
	}
	void SetVertices(VERTEX_TYPE *vertices,unsigned int verticesSize, GLuint usage = GL_STATIC_DRAW) {
		//Bind buffer
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _vbos[0]));
		//Upload data
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX_TYPE)*verticesSize, vertices, usage));
		//Unbind buffer
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, NULL));

		_verticesSize = verticesSize;
	}
	void SetIndices(unsigned int *indices, unsigned int indicesSize, GLuint usage = GL_STATIC_DRAW) {

		//Bind the index buffer
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[1]));
		//Upload indices
		GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesSize, indices, usage));
		//Unbind buffer
		GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL));

		_indicesSize = indicesSize;
	}

	void Bind() {
		//Bind VAO
		GL_CHECK(glBindVertexArray(_vao));
	}

	void Draw(GLenum mode = GL_TRIANGLES) {

		GL_CHECK(glDrawElements(mode, _verticesSize, GL_UNSIGNED_INT, 0)); // Draw our square  

	}
	void Unbind() {

		//Bind VAO
		GL_CHECK(glBindVertexArray(0));	
	}

	//Loads an origin cented unit quad
	void LoadQuad() {
		VERTEX_TYPE * vertices;
		unsigned int verticesSize;
		unsigned int indicesSize;
		unsigned int* indices;
		unsigned int size = 0;
		VERTEX_TYPE::GetQuad(vertices, verticesSize, indices, indicesSize);
		SetVertices(vertices, verticesSize);
		SetIndices(indices, indicesSize);
		//Delete the CPU buffers
		delete[] vertices;
		delete[] indices;
	}

private:

	//Vertex array object handle
	GLuint _vao;

	//Vertex and index buffer handle
	GLuint _vbos[2];

	unsigned int _verticesSize;
	unsigned int _indicesSize;
};