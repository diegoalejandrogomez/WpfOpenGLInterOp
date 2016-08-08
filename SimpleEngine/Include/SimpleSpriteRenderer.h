#pragma once
#include "stdafx.h"
#include "SimpleObject.h"
#include "VertexFormats.h"
#include "SimpleCamera2D.h"
#include "SimpleMesh.h"
#include "SimpleTexture.h"

class SimpleShaderProgram;

class SimpleSpriteRenderer : public SimpleObject {
public:

	SimpleSpriteRenderer();
	void Advance(float dt);
	void Render(float dt);
	void SetAsTexture(std::string && name);
	void SetAsTextureRect(std::string && name, glm::vec2 offset, glm::vec2 size);
	~SimpleSpriteRenderer();

	inline SimpleTexture* GetTexture() { return _tex; };

private:
	unsigned int _vertexCount;
	unsigned int _indexCount;
	GLuint _vao;	//vertex array object
	GLuint _vbos[2]; //Position and color in the same buffer and indexes in a separate one
	SimpleShaderProgram* _shader;
	SimpleCamera2D* _cam;

	//A simple mesh using positions and texture coordinates
	SimpleMesh<VertexTextureFormat2D> *_mesh;
	//Texture used for renering
	SimpleTexture* _tex;
	
	//Offset and size in pixel coordinates (to make life easier to the user)
	glm::vec2 _rectOffset;
	glm::vec2 _rectSize;
	
};

