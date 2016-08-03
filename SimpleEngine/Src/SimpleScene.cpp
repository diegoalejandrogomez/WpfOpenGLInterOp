#include "stdafx.h"
#include "SimpleScene.h"


SimpleScene::SimpleScene() {
	_camera = new SimpleCamera2D();
}

SimpleScene::~SimpleScene() {
	
	if (_camera != nullptr)
		delete _camera;

	for (auto& ent : _entities)
		delete ent;
	
	_entities.clear();
}

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


void SimpleScene::RemoveEntity(SimpleObject* sObj) {
	auto it = find(_entities.begin(), _entities.end(), sObj);
	if (it != _entities.end())
		_entities.erase(it);
}

