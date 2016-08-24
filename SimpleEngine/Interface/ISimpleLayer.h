#pragma once
#include "SimpleLayer.h"

extern "C" {
	SIMPLE_API void SimpleLayer_AddEntity(SimpleLayer* sLayer, SimpleObject* sObj);
	SIMPLE_API bool SimpleLayer_Remove(SimpleLayer* sLayer, SimpleObject* sObj);
	SIMPLE_API void SimpleLayer_Clear(SimpleLayer* sLayer, bool deleteEntities = false);

	SIMPLE_API	void SimpleLayer_SetZ(SimpleLayer* sLayer, float Z);
	SIMPLE_API float SimpleLayer_GetZ(SimpleLayer* sLayer);

	SIMPLE_API inline const SimpleID& SimpleLayer_GetName(SimpleLayer* sLayer);
	SIMPLE_API inline void  SimpleLayer_SetName(SimpleLayer* sLayer, SimpleID name);

	SIMPLE_API inline void SimpleLayer_SetQueryable(SimpleLayer* sLayer, bool value);
	SIMPLE_API inline bool SimpleLayer_IsQueryable(SimpleLayer* sLayer);

	//json not available in C
	//SIMPLE_API json SimpleLayer_Serialize(SimpleLayer* sLayer);
	//SIMPLE_API bool SimpleLayer_Deserialize(SimpleLayer* sLayer, json& layer);
	
	SIMPLE_API SimpleObject* SimpleLayer_EntitiesBegin(SimpleLayer* layer);

	SIMPLE_API SimpleObject* SimpleLayer_EntitiesNext(SimpleLayer* layer);
	SIMPLE_API SimpleObject* SimpleLayer_EntitiesEnd(SimpleLayer* layer);
	int entIt;
}