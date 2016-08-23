#include "stdafx.h"
#include "ISimpleLayer.h"

SIMPLE_API SimpleObject* SimpleLayer_EntitiesBegin(SimpleLayer* layer) {

	auto entities = layer->GetEntities();

	if (entities.size() == 0)
		return nullptr;

	entIt = 0;
	return entities[entIt++];
}

SIMPLE_API SimpleObject* SimpleLayer_EntitiesNext(SimpleLayer* layer) {
	auto entities = layer->GetEntities();

	if (entIt >= entities.size() - 1)
		return nullptr;
	return entities[entIt++];

}
SIMPLE_API SimpleObject* SimpleLayer_EntitiesEnd(SimpleLayer* layer) {
	return nullptr;
}

SIMPLE_API void AddEntity(SimpleLayer* sLayer, SimpleObject * sObj)
{
	sLayer->AddEntity(sObj);
}

SIMPLE_API bool RemoveEntity(SimpleLayer* sLayer, SimpleObject * sObj)
{
	return sLayer->RemoveEntity(sObj);
}

SIMPLE_API void Clear(SimpleLayer* sLayer, bool deleteEntities)
{
	return sLayer->Clear(deleteEntities);
}
     
SIMPLE_API void SetZ(SimpleLayer* sLayer, float Z)
{
	sLayer->SetZ(Z);
}

SIMPLE_API float GetZ(SimpleLayer* sLayer)
{
	return sLayer->GetZ();
}

inline SIMPLE_API const SimpleID & GetName(SimpleLayer* sLayer)
{
	return sLayer->GetName();
}

SIMPLE_API void SetName(SimpleLayer* sLayer, SimpleID name)
{
	sLayer->SetName(name);
}

SIMPLE_API void SetQueryable(SimpleLayer* sLayer, bool value)
{
	sLayer->SetQueryable(value);
}

SIMPLE_API bool IsQueryable(SimpleLayer* sLayer)
{
	return sLayer->IsQueryable();
}
