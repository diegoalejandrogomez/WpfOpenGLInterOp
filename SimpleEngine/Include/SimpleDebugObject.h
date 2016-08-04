#pragma once
#include "stdafx.h"
#include "SimpleObject.h"
#include "VertexFormats.h"
#include "SimpleCamera2D.h"
class SimpleShaderProgram;

class SimpleDebugObject : public SimpleObject{
public:

	SimpleDebugObject();
	void Advance(float dt);
	void Render(float dt);

private:
	unsigned int _vertexCount;
	unsigned int _indexCount;
	GLuint _vao;	//vertex array object
	GLuint _vbos[2]; //Position and color in the same buffer and indexes in a separate one
	SimpleShaderProgram* _shader;
	SimpleCamera2D* _cam;
	void _GeneratePositionAndColor(	VertexColorFormat2D* &vertexs,
									unsigned int &verticesSize,
									unsigned int* &indices,
									unsigned int &indicesSize);

};
