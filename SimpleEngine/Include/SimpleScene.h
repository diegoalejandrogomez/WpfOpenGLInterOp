#pragma once
#include "SimpleObject.h"
#include <vector>
#include "SimpleCamera2D.h"

class SimpleScene {
	//Only 1 camera per scene
	SimpleCamera2D* _camera;
	std::vector<SimpleObject*> _entities;

public:

	SimpleScene();
	void Render(float dt);
	void Advance(float dt);
	void AddEntity(SimpleObject* sObj);
	void RemoveEntity(SimpleObject* sObj);
	
	inline SimpleCamera2D* GetCamera() { return _camera; };

	const std::vector<SimpleObject*>& GetEntities() { return _entities; };

};