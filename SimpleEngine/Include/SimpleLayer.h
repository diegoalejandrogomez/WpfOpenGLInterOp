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
	typedef std::vector<SimpleObject*> SimpleObjectList;

	const SimpleObjectList& GetEntities();
	
	void AddEntity(SimpleObject* sObj);
	bool RemoveEntity(const SimpleObject* sObj);
	void Clear(bool deleteEntities = false);

	void SetZ(float Z);
	float GetZ() const;
	
	inline const SimpleID& GetName() const { return _layerName; }
	inline void  SetName(SimpleID name) {_layerName = name; }

	inline void SetQueryable(bool value) { _queryable = value; };
	inline bool IsQueryable() const { return _queryable; };
	
	json Serialize() override;
	bool Deserialize(const json& layer) override;

protected:
	SimpleObjectList _entities;
	float Z;
	SimpleID _layerName;
	bool _queryable;
	
};