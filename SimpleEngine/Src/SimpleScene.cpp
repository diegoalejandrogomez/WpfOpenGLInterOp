#include "stdafx.h"
#include <vector>
#include <algorithm>
#include "SimpleScene.h"
#include "stdlib.h"
#include "LowerzIndex.h"
#include "SimpleEngine.h"
#include <algorithm>

SimpleScene::SimpleScene() {
	
	_camera = new SimpleCamera2D();
	//Create a default layer at z = 0
	auto layer = new SimpleLayer();
	layer->SetZ(0);
	AddLayer(layer);

	//Initialize spatial query auxiliaries
	_queryResults.reserve(_maxQueryResults);
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

void SimpleScene::AddEntity(SimpleObject* sObj, int nLayer) {
	SimpleLayer* layer = GetLayer(nLayer);
	if(layer != nullptr)
		layer->AddEntity(sObj);
}

void SimpleScene::AddEntity(SimpleObject* sObj, std::string layerName) {
	
	SimpleLayer* layer = GetLayer(layerName);
	if (layer != nullptr)
		layer->AddEntity(sObj);
}

void SimpleScene::AddEntity(SimpleObject* sObj, SimpleLayer* sLay) {
	sLay->AddEntity(sObj);
}

SimpleLayer* SimpleScene::GetLayer(int nLayer) {
	auto layer = find_if(_layers.begin(), _layers.end(), [&nLayer](SimpleLayer* l) {return l->GetZ() == nLayer;});
	if (layer != _layers.end())
		return *layer;

	return nullptr;
}

SimpleLayer* SimpleScene::GetLayer(std::string layerName) {
	
	auto layer = find_if(_layers.begin(), _layers.end(), [&layerName](SimpleLayer* l) {return l->GetName() == layerName;});
	if (layer != _layers.end())
		return *layer;
	return nullptr;

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


//Returns all the entities at point
std::vector<SimpleObject*>& SimpleScene::PickAll(glm::vec2 point) {
	_queryResults.clear();
	for (SimpleLayer* &l : _layers) {
		for (SimpleObject* obj : l->GetEntities()) {
			if (obj->GetAABB().Contains(obj->GetTransform(), point.x, point.y))
				_queryResults.push_back(obj);
			if (_queryResults.size() == _maxQueryResults)
				return _queryResults;
		}
	}
	return _queryResults;

	

}
//Returns all the entities that overlap rect
std::vector<SimpleObject*>& SimpleScene::PickAll(SimpleAABB rect) {
	_queryResults.clear();
	for (SimpleLayer* &l : _layers) {
		for (SimpleObject* obj : l->GetEntities()) {
			if(rect.Overlaps(glm::mat4(1.0f), obj->GetAABB(), obj->GetTransform()))
				_queryResults.push_back(obj);
			if (_queryResults.size() == _maxQueryResults)
				return _queryResults;
		}
	}
	return _queryResults;
}

//Returns the first entity at point
SimpleObject* SimpleScene::PickFirst(glm::vec2 point) {
	for (SimpleLayer* &l : _layers) {
		for (SimpleObject* obj : l->GetEntities()) {
			if (obj->GetAABB().Contains(obj->GetTransform(),point.x, point.y))
				return obj;
		}
	}
	return nullptr;
}

//Returns the first entity that overlaps
SimpleObject* SimpleScene::PickFirst(SimpleAABB rect) {
	for (SimpleLayer* &l : _layers) {
		for (SimpleObject* obj : l->GetEntities()) {
			if (rect.Overlaps(glm::mat4(1.0f), obj->GetAABB(), obj->GetTransform()))
				return obj;	
		}
	}
	return nullptr;
}


float SimpleScene::GetFPS() {
	return SimpleEngine::Instance()->GetRenderFPS();
}