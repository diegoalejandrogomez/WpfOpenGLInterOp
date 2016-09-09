#pragma once
#include "stdafx.h"
#include "SimpleObject.h"
#include "SimpleSpriteRenderer.h"
#include "SimpleEngine.h"
#include "SimpleConfiguration.h"



class SIMPLE_API SimpleLineRenderer : public SimpleObject {
public:

	SimpleLineRenderer();
	void Advance(float dt);
	void Render(float dt);
	~SimpleLineRenderer();

	
	void AddLine(glm::vec2 from, glm::vec2 to, glm::vec3 color);
	void Flush();
	void ClearLines();

	virtual SimpleID GetType() { return "SimpleLineRenderer"; }
	virtual json Serialize() override;
	virtual bool Deserialize(const json &node) override;
	virtual bool Deserialize(const json &node, std::string dir);
private:

	
	unsigned int _vertexCount;
	unsigned int _indexCount;
	GLuint _vao;	//vertex array object
	GLuint _vbos[2]; //Position and color in the same buffer and indexes in a separate one
	SimpleShaderProgram* _shader;
	SimpleCamera2D* _cam;

	//A simple mesh using positions and colors
	SimpleMesh<VertexColorFormat2D> *_mesh;
	
	//Line collection
	std::vector<VertexColorFormat2D> _vertices;
		

};
