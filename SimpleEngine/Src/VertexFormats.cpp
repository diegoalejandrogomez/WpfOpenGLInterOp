#include "stdafx.h"
#include "VertexFormats.h"


void VertexColorFormat2D::Bind(int index) {
	GL_CHECK(glVertexAttribFormat(0, 2, GL_FLOAT, GL_FALSE, offsetof(VertexColorFormat2D, pos)));
	GL_CHECK(glVertexAttribBinding(0, index));
	GL_CHECK(glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, offsetof(VertexColorFormat2D, color)));
	GL_CHECK(glVertexAttribBinding(1, index));
	//Enable vertex attributes 0 and 1 for position and colour
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glEnableVertexAttribArray(1));

}

//returns an unit origin centered quad. Returns ownership of the allocated memory
void VertexColorFormat2DGetQuad(VertexColorFormat2D* &vertexs,
	unsigned int &verticesSize,
	unsigned int* &indices,
	unsigned int &indicesSize) {

	float halfSize = 0.5f;
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


void VertexTextureFormat2D::Bind(int index) {
	GL_CHECK(glVertexAttribFormat(0, 2, GL_FLOAT, GL_FALSE, offsetof(VertexTextureFormat2D, pos)));
	GL_CHECK(glVertexAttribBinding(0, index));
	GL_CHECK(glVertexAttribFormat(1, 2, GL_FLOAT, GL_FALSE, offsetof(VertexTextureFormat2D, uv)));
	GL_CHECK(glVertexAttribBinding(1, index));

	//Enable vertex attributes 0 and 1 for position and uvs
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glEnableVertexAttribArray(1));
}

//returns an unit origin centered quad. Returns ownership of the allocated memory
void VertexTextureFormat2D::GetQuad(VertexTextureFormat2D* &vertexs,
	unsigned int &verticesSize,
	unsigned int* &indices,
	unsigned int &indicesSize) {

	float halfSize = 0.5f;
	verticesSize = 4;
	vertexs = new VertexTextureFormat2D[12];
	indices = new unsigned int[6];
	indicesSize = 6;


	vertexs[0].pos[0] = -halfSize; vertexs[0].pos[1] = -halfSize;	// Bottom left corner  
	vertexs[0].uv[0] = 0.0; vertexs[0].uv[1] = 0.0;					// Bottom left corner  

	vertexs[1].pos[0] = -halfSize; vertexs[1].pos[1] = halfSize;	// Top left corner  
	vertexs[1].uv[0] = 0.0; vertexs[1].uv[1] = 1.0;					// Top left corner  

	vertexs[2].pos[0] = halfSize; vertexs[2].pos[1] = halfSize;		// Top Right corner  
	vertexs[2].uv[0] = 1.0; vertexs[2].uv[1] = 1.0;					// Top Right corner  

	vertexs[3].pos[0] = halfSize; vertexs[3].pos[1] = -halfSize;	// Bottom right corner  
	vertexs[3].uv[0] = 1.0; vertexs[3].uv[1] = 0.0;					// Bottom right corner  

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
}