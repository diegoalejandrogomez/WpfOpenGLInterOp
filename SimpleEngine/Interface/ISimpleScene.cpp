#include "stdafx.h"
#include "ISimpleScene.h"
#include "SimpleScene.h"
#include "SimpleEngine.h"
void SimpleScene_AddEntityWithIdx(SimpleObject* sObj, int nLayer) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		scene->AddEntity(sObj, nLayer);

}
void SimpleScene_AddEntityWithName(SimpleObject* sObj, const char* layerName) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		scene->AddEntity(sObj, layerName);

}
void SimpleScene_AddEntityWithLayer(SimpleObject* sObj, SimpleLayer* sLayer) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		scene->AddEntity(sObj, sLayer);

}

void SimpleScene_RemoveEntityWithLayer(SimpleObject* sObj, SimpleLayer* sLayer) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		scene->RemoveEntity(sObj, sLayer);

}
void SimpleScene_RemoveEntityWithName(SimpleObject* sObj, const char* sLayer) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		scene->RemoveEntity(sObj, sLayer);

}
void SimpleScene_RemoveEntity(SimpleObject* sObj) {
	
	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		scene->RemoveEntity(sObj);
}


void SimpleScene_AddLayer(SimpleLayer* sLayer) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		scene->AddLayer(sLayer);

}
void SimpleScene_RemoveLayer(SimpleLayer* sLayer) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		scene->RemoveLayer(sLayer);

}

uint32_t GetLayerCount() {
	
	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		return scene->GetLayers().size();
	return 0;

}
SimpleLayer* SimpleScene_GetLayerWithIdx(int nLayer) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		return scene->GetLayer(nLayer);
	return nullptr;
	
}
SimpleLayer* SimpleScene_GetLayerWithName(SimpleID layerName) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		return scene->GetLayer(layerName);
	return nullptr;

}


float SimpleScene_GetLowerZIndex() {
	
	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		scene->GetLowerZIndex();
	return 0.0f;

}
float SimpleScene_GetFPS() {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		return scene->GetFPS();
	return 0.0f;
}


SimpleObject* SimpleScene_PickFirstPoint(float x, float y) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		return scene->PickFirst({ x,y });
	return nullptr;
}
SimpleObject* SimpleScene_PickFirstPointInLayer(float x, float y, SimpleLayer* l) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr)
		return scene->PickFirst({ x,y }, l);
	return nullptr;
}

SimpleObject* SimpleScene_PickFirstAABB(float x, float y, float width, float height) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr) {
		SimpleAABB aabb;
		aabb.position = { x, y, 0.0f };
		aabb.size = {width, height};
		return scene->PickFirst(aabb);
	}
	return nullptr;

}
SimpleObject* SimpleScene_PickFirstAABBInLayer(float x, float y, float width, float height, SimpleLayer* l) {

	SimpleScene *scene = SimpleEngine::Instance()->GetScene();
	if (scene != nullptr) {
		SimpleAABB aabb;
		aabb.position = { x, y, 0.0f };
		aabb.size = { width, height };
		return scene->PickFirst(aabb, l);
	}
	return nullptr;

}