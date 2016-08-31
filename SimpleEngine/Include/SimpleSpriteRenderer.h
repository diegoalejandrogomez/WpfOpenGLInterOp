#pragma once
#include "stdafx.h"
#include "SimpleObject.h"
#include "VertexFormats.h"
#include "SimpleCamera2D.h"
#include "SimpleMesh.h"
#include "SimpleTexture.h"
#include "SimpleConfiguration.h"
class SimpleShaderProgram;

class SIMPLE_API SimpleSpriteRenderer : public SimpleObject {
public:

	SimpleSpriteRenderer();
	~SimpleSpriteRenderer();
	virtual void Advance(float dt);
	virtual void Render(float dt);
	void SetAsTexture(std::string && name);
	void SetAsTextureRect(std::string && name, glm::vec2 offset, glm::vec2 size);
	void SetAsTexture(SimpleTexture *t);
	void SetAsTextureRect(SimpleTexture *t, glm::vec2 offset, glm::vec2 size);
	void SetRect(glm::vec2 offset, glm::vec2 size);
	void SnapToGrid(bool snap) { _snapToGrid = snap; };
	void SetSnapGridSize(glm::vec2 snapGridSize) { _snapSize = snapGridSize; };
	
	//Overrides the default shader
	void SetShader(SimpleShaderProgram* shader) { _shader = shader; }

	inline SimpleTexture* GetTexture() { return _tex; };

	virtual SimpleID GetType() { return "SimpleSpriteRenderer"; }
	virtual json Serialize();
	virtual bool Deserialize(const json &node);
	

protected:
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

	//Snapping utilities
	bool _snapToGrid;
	glm::vec2 _snapSize;	

private:
		
	
};

