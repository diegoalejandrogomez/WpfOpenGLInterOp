#include "stdafx.h"
#include <vector>
#include <algorithm>
#include "SimpleScene.h"
#include "stdlib.h"
#include "LowerzIndex.h"

SimpleScene::SimpleScene() {
	_camera = new SimpleCamera2D();
}

SimpleScene::~SimpleScene() {
	
	if (_camera != nullptr)
		delete _camera;

	for (auto& layer : _layers)
		delete layer;
	
	_layers.clear();
}

void SimpleScene::Render(float dt) {

	for (auto& layer : _layers)
	{
		for (auto &entity : layer->GetEntities())
			entity->Render(dt);
	}
	
}


void SimpleScene::Advance(float dt) {
	for (auto& layer : _layers)
	{
		for (auto &entity : layer->GetEntities())
			entity->Advance(dt);
	}
}

void SimpleScene::AddEntity(SimpleObject* sObj, SimpleLayer* sLay) {
	sLay->AddEntity(sObj);
}

void SimpleScene::RemoveEntity(SimpleObject* sObj, SimpleLayer* sLay) {
	sLay->RemoveEntity(sObj);
}

void SimpleScene::AddLayer(SimpleLayer* sLayer){
	std::vector<SimpleLayer*>::iterator it = std::lower_bound(_layers.begin(), _layers.end(), sLayer, LowerZIndex()); // find proper position in descending order
	_layers.insert(it, sLayer);
}

void SimpleScene::RemoveLayer(SimpleLayer* sLayer) {
	auto it = find(_layers.begin(), _layers.end(), sLayer);
	if (it != _layers.end())
		_layers.erase(it);
}

float SimpleScene::GetLowerZIndex() {
	std::vector<SimpleLayer*> layers = GetLayers();
	float min = 10000;
	for (auto layer : layers) // access by reference to avoid copying
	{
		if (layer->GetZ() < min)
		{
			min = layer->GetZ();
		}
	}

	return min;
}
