#pragma once
#include "SimpleConfiguration.h"

struct SIMPLE_API VertexColorFormat2D {
	float pos[2];	//xy
	float color[3]; //rgb

	static void Bind(int index);

	//returns an unit origin centered quad. Returns ownership of the allocated memory
	static void GetQuad(VertexColorFormat2D* &vertexs,
		unsigned int &verticesSize,
		unsigned int* &indices,
		unsigned int &indicesSize);
};


struct SIMPLE_API VertexTextureFormat2D {
	float pos[2];	//xy
	float uv[2]; //uv 

	static void Bind(int index);
	//returns an unit origin centered quad. Returns ownership of the allocated memory
	static void GetQuad(VertexTextureFormat2D* &vertexs,
		unsigned int &verticesSize,
		unsigned int* &indices,
		unsigned int &indicesSize);
};