#include "stdafx.h"
#include "SimpleLayer.h"

SimpleLayer::SimpleLayer() : 
	_layerName(""), _queryable(true){
		
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
	if(_layerName.HasString())
		layer["nameVerbose"] = static_cast<std::string>(_layerName.GetString());

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


bool SimpleLayer::Deserialize(json& layer) {
	
	if (layer.find("name") == layer.end()) {
		SIMPLE_LOG("Couldn't find name field in layer");
		return false;
	}
	
	if (layer.find("nameVerbose") != layer.end())
		_layerName = layer["nameVerbose"].get<std::string>();	
	else
		_layerName =  static_cast<SimpleID::Type>(layer["name"]);
	 
	if (layer.find("z") == layer.end()) {
		SIMPLE_LOG("Couldn't find z field in layer");
		return false;
	}
	Z = layer["z"];

	if (layer.find("queryable") == layer.end()) {
		SIMPLE_LOG("Couldn't find queryable field in layer");
		return false;
	}
	_queryable = layer["queryable"];

	if (layer.find("entities") == layer.end()) {
		SIMPLE_LOG("Couldn't find entities field in layer");
		return false;
	}
	
	//// range-based for
	for (auto& e : layer["entities"]) {

		if (e.find("type") == e.end())
			return false;
		SimpleObject* obj = SimpleObject::BaseFactory::CreateInstance((SimpleID::Type)e["type"]);
		obj->Deserialize(e);
		AddEntity(obj);
	}

	return true;
}