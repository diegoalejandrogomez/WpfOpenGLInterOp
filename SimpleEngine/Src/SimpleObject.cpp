#include "stdafx.h"
#include "SimpleObject.h"
#include <glm\gtx\transform.hpp>


const glm::mat4 SimpleObject::GetTransform()const {
	//We don't have scale for now...
	return  glm::translate(_aabb.position) * glm::rotate(_orientation, glm::vec3(0.0f, 0.0f, 1.0f));

}


json SimpleObject::Serialize() {

	json ret{
			{"type", static_cast<SimpleID::Type>(GetType()) },
			{"name", static_cast<SimpleID::Type>(_name)},
			{"aabb",{
					{"position", {_aabb.position.x, _aabb.position.y, _aabb.position.z}},
					{"size", {_aabb.size.x, _aabb.size.y}}
					}
			},
			{"orientation", _orientation}
	};
	
	return ret;	
}


void SimpleObject::Deserialize(json &node) {
	_name = (SimpleID::Type)node["name"];
	_aabb.position.x = node["aabb"]["position"][0];
	_aabb.position.y = node["aabb"]["position"][1];
	_aabb.position.z = node["aabb"]["position"][2];

	_aabb.size.x = node["aabb"]["size"][0];
	_aabb.size.y = node["aabb"]["size"][1];

	_orientation = node["orientation"];
}