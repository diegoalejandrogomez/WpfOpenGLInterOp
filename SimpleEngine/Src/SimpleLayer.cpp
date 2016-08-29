#include "stdafx.h"
#include "SimpleLayer.h"

SimpleLayer::SimpleLayer() : 
	_layerName(""), _queryable(true) {		
}


const SimpleLayer::SimpleObjectList &SimpleLayer::GetEntities() {
	return this->_entities;
}

SimpleLayer::~SimpleLayer() {
	this->Clear(true);
	_entities.clear();
}

void SimpleLayer::AddEntity(SimpleObject* sObj) {
	_entities.push_back(sObj);
}


bool SimpleLayer::RemoveEntity(const SimpleObject* sObj) {
	const size_t size = _entities.size(); // caching the vector size
	_entities.erase(std::remove(_entities.begin(), _entities.end(), sObj), _entities.end());
	return _entities.size() < size;
}

void SimpleLayer::Clear(bool deleteEntities) {
	if (deleteEntities) {
		std::for_each(_entities.begin(), _entities.end(), std::default_delete<SimpleObject>());
	}
	_entities.clear();
}

void SimpleLayer::SetZ(float Z) {
	this->Z = Z;
}

float SimpleLayer::GetZ() const {
	return this->Z;
}


json SimpleLayer::Serialize() {
	json layer;
	layer["name"] = static_cast<SimpleID::Type>(_layerName);
	if(_layerName.HasString())
		layer["nameVerbose"] = _layerName.GetString();

	layer["z"] = Z;
	layer["queryable"] = _queryable;
	
	json elements = json::array();
	std::for_each(_entities.begin(), _entities.end(), [&elements](SimpleObject* entity) { if (entity->IsSerializable()) {
			elements.push_back(entity->Serialize());
		}
	});

	layer["entities"] = elements;
	
	return layer;
}


bool SimpleLayer::Deserialize(const json& layer) {
	
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
		if (obj->Deserialize(e))
			AddEntity(obj);
	}

	return true;
}