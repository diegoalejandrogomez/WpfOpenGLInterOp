#include "stdafx.h"
#include "ISimpleScene.h"
#include "SimpleScene.h"
#include "SimpleEngine.h"

extern "C"
{
	SIMPLE_API void SimpleScene_AddEntityWithIdx(SimpleObject* sObj, int nLayer) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			scene->AddEntity(sObj, nLayer);

	}
	SIMPLE_API void SimpleScene_AddEntityWithName(SimpleObject* sObj, const char* layerName) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			scene->AddEntity(sObj, layerName);

	}
	SIMPLE_API void SimpleScene_AddEntityWithLayer(SimpleObject* sObj, SimpleLayer* sLayer) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			scene->AddEntity(sObj, sLayer);

	}

	SIMPLE_API void SimpleScene_RemoveEntityWithLayer(SimpleObject* sObj, SimpleLayer* sLayer) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			scene->RemoveEntity(sObj, sLayer);

	}
	SIMPLE_API void SimpleScene_RemoveEntityWithName(SimpleObject* sObj, const char* sLayer) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			scene->RemoveEntity(sObj, sLayer);

	}
	SIMPLE_API void SimpleScene_RemoveEntity(SimpleObject* sObj) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			scene->RemoveEntity(sObj);
	}


	SIMPLE_API void SimpleScene_AddLayer(SimpleLayer* sLayer) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			scene->AddLayer(sLayer);

	}
	SIMPLE_API void SimpleScene_RemoveLayer(SimpleLayer* sLayer) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			scene->RemoveLayer(sLayer);

	}

	SIMPLE_API uint32_t GetLayerCount() {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			return scene->GetLayers().size();
		return 0;

	}
	SIMPLE_API SimpleLayer* SimpleScene_GetLayerWithIdx(int nLayer) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			return scene->GetLayer(nLayer);
		return nullptr;

	}
	SIMPLE_API SimpleLayer* SimpleScene_GetLayerWithName(SimpleID layerName) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			return scene->GetLayer(layerName);
		return nullptr;

	}


	SIMPLE_API float SimpleScene_GetLowerZIndex() {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			scene->GetLowerZIndex();
		return 0.0f;

	}
	SIMPLE_API float SimpleScene_GetFPS() {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			return scene->GetFPS();
		return 0.0f;
	}


	SIMPLE_API SimpleObject* SimpleScene_PickFirstPoint(float x, float y) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			return scene->PickFirst({ x,y });
		return nullptr;
	}
	SIMPLE_API SimpleObject* SimpleScene_PickFirstPointInLayer(float x, float y, SimpleLayer* l) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr)
			return scene->PickFirst({ x,y }, l);
		return nullptr;
	}

	SIMPLE_API SimpleObject* SimpleScene_PickFirstAABB(float x, float y, float width, float height) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr) {
			SimpleAABB aabb;
			aabb.position = { x, y, 0.0f };
			aabb.size = { width, height };
			return scene->PickFirst(aabb);
		}
		return nullptr;

	}
	SIMPLE_API SimpleObject* SimpleScene_PickFirstAABBInLayer(float x, float y, float width, float height, SimpleLayer* l) {

		SimpleScene *scene = SimpleEngine::Instance()->GetScene();
		if (scene != nullptr) {
			SimpleAABB aabb;
			aabb.position = { x, y, 0.0f };
			aabb.size = { width, height };
			return scene->PickFirst(aabb, l);
		}
		return nullptr;

	}
}