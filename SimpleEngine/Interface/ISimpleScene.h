#pragma once
#include "SimpleScene.h"
#include "SimpleObject.h"
#include "SimpleConfiguration.h"
#include "SimpleLayer.h"

extern "C" {

	SIMPLE_API void SimpleScene_AddEntityWithIdx(SimpleObject* sObj, int nLayer);
	SIMPLE_API void SimpleScene_AddEntityWithName(SimpleObject* sObj, const char* layerName);
	SIMPLE_API void SimpleScene_AddEntityWithWithLayer(SimpleObject* sObj, SimpleLayer* sLayer);

	SIMPLE_API void SimpleScene_RemoveEntityWithLayer(SimpleObject* sObj, SimpleLayer* sLayer);
	SIMPLE_API void SimpleScene_RemoveEntityWithName(SimpleObject* sObj, const char* sLayer);
	SIMPLE_API void SimpleScene_RemoveEntity(SimpleObject* sObj);
	
	SIMPLE_API void SimpleScene_AddLayer(SimpleLayer* sLayer);
	SIMPLE_API void SimpleScene_RemoveLayer(SimpleLayer* sLayer);

	SIMPLE_API SimpleLayer* SimpleScene_GetLayerWithIdx(int nLayer);
	SIMPLE_API SimpleLayer* SimpleScene_GetLayerWithName(SimpleID layerName);
	
	SIMPLE_API uint32_t GetLayerCount();
		
	SIMPLE_API float SimpleScene_GetLowerZIndex();
	SIMPLE_API float SimpleScene_GetFPS();

	//Returns the first entity at point

	SIMPLE_API SimpleObject* SimpleScene_PickFirstPoint(float x, float y);
	SIMPLE_API SimpleObject* SimpleScene_PickFirstPointInLayer(float x, float y, SimpleLayer* l);
		
	SIMPLE_API SimpleObject* SimpleScene_PickFirstAABB(float x, float y, float width, float height);
	SIMPLE_API SimpleObject* SimpleScene_PickFirstAABBInLayer(float x, float y, float width, float height, SimpleLayer* l);


}
