#pragma once
#include "SimpleLayer.h"

extern "C" {
	SIMPLE_API void AddEntity(SimpleLayer* sLayer, SimpleObject* sObj);
	SIMPLE_API bool RemoveEntity(SimpleLayer* sLayer, SimpleObject* sObj);
	SIMPLE_API void Clear(SimpleLayer* sLayer, bool deleteEntities = false);

	SIMPLE_API	void SetZ(SimpleLayer* sLayer, float Z);
	SIMPLE_API float GetZ(SimpleLayer* sLayer);

	SIMPLE_API inline const SimpleID& GetName(SimpleLayer* sLayer);
	SIMPLE_API inline void  SetName(SimpleLayer* sLayer, SimpleID name);

	SIMPLE_API inline void SetQueryable(SimpleLayer* sLayer, bool value);
	SIMPLE_API inline bool IsQueryable(SimpleLayer* sLayer);

	SIMPLE_API json Serialize(SimpleLayer* sLayer);
	SIMPLE_API bool Deserialize(SimpleLayer* sLayer, json& layer);
	
	SIMPLE_API SimpleObject* SimpleLayer_EntitiesBegin(SimpleLayer* layer);

	SIMPLE_API SimpleObject* SimpleLayer_EntitiesNext(SimpleLayer* layer);
	SIMPLE_API SimpleObject* SimpleLayer_EntitiesEnd(SimpleLayer* layer);
	int entIt;
}