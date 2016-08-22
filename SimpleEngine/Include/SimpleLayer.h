#pragma once
#include <stdlib.h>
#include <vector>
#include "SimpleObject.h"
#include "SimpleSerializable.h"
#include "SimpleConfiguration.h"

class SIMPLE_API SimpleLayer : public SimpleSerializable{
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
	
	virtual json Serialize() override;
	virtual bool Deserialize(json& layer) override;

protected:
	std::vector<SimpleObject*> _entities;
	float Z;
	SimpleID _layerName;
	bool _queryable;
	
};