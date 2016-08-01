#include "stdafx.h"
#include "SimpleScene.h"

void SimpleScene::Render(float dt) {

	for (auto &entity : _entities)
		entity->Render(dt);

}


void SimpleScene::Advance(float dt) {

	for (auto &entity : _entities)
		entity->Advance(dt);

}


void SimpleScene::AddEntity(SimpleObject* sObj){
	
	_entities.push_back(sObj);
}