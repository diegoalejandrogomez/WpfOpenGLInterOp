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
	inline const std::string& GetName()const { return _layerName; }
	inline void  SetName(std::string name) {_layerName = name; }
private:
	std::vector<SimpleObject*> _entities;
	float Z;
	std::string _layerName;
};