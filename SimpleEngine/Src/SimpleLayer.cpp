#include "stdafx.h"
#include "SimpleLayer.h"

SimpleLayer::SimpleLayer():_layerName ("") {
	_queryable = true;
}


const std::vector<SimpleObject*>& SimpleLayer::GetEntities()
{
	return this->_entities;
}

SimpleLayer::~SimpleLayer() {

	for (auto& ent : _entities)
		delete ent;

	_entities.clear();
}

void SimpleLayer::AddEntity(SimpleObject* sObj) {

	_entities.push_back(sObj);
}


bool SimpleLayer::RemoveEntity(SimpleObject* sObj) {
	auto it = find(_entities.begin(), _entities.end(), sObj);
	if (it != _entities.end()) {
		_entities.erase(it);
		return true;
	}
	return false;
}

void SimpleLayer::Clear(bool deleteEntities) {
	if (deleteEntities)
		for (auto e : _entities)
			delete e;
	_entities.clear();
}

void SimpleLayer::SetZ(float Z) {
	this->Z = Z;
}

float SimpleLayer::GetZ() {
	return this->Z;
}


json SimpleLayer::Serialize() {

	json layer;
	layer["name"] = static_cast<SimpleID::Type>(_layerName);
	layer["z"] = Z;
	layer["queryable"] = _queryable;
	
	json elements = json::array();
	for (auto entity : _entities) {
		json e  = entity->Serialize();
		elements.push_back(e);
	}
	layer["entities"] = elements;
	
	return layer;

}