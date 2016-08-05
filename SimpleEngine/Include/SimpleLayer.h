#pragma once
#include <stdlib.h>
#include <vector>
#include "SimpleObject.h"

class SimpleLayer {
public:
	SimpleLayer();
	~SimpleLayer();
	const std::vector<SimpleObject*>& GetEntities();
	void AddEntity(SimpleObject* sObj);
	void RemoveEntity(SimpleObject* sObj);
	void SetZ(float Z);
	float GetZ();
private:
	std::vector<SimpleObject*> _entities;
	float Z;
};