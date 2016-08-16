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
	bool RemoveEntity(SimpleObject* sObj);
	void Clear(bool deleteEntities = false);

	void SetZ(float Z);
	float GetZ();
	
	inline const SimpleID& GetName()const { return _layerName; }
	inline void  SetName(SimpleID name) {_layerName = name; }

	inline void SetQueryable(bool value) { _queryable = value; };
	inline bool IsQueryable() { return _queryable; };
private:
	std::vector<SimpleObject*> _entities;
	float Z;
	SimpleID _layerName;
	bool _queryable;
};