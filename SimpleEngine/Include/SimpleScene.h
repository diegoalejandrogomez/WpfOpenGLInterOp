#pragma once
#include "SimpleObject.h"
#include <vector>

class SimpleScene {

	std::vector<SimpleObject*> _entities;

public:

	void Render(float dt);
	void Advance(float dt);
	void AddEntity(SimpleObject* sObj);
	void RemoveEntity(SimpleObject* sObj);

	const std::vector<SimpleObject*>& GetEntities() { return _entities; };

};