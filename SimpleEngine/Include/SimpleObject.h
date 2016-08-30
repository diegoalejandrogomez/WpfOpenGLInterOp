#pragma once
#include <tuple>
#include <glm\glm.hpp>
#include "SimpleAABB.h"
#include "SimpleID.h"
#include "json.hpp"
#include "SimpleFactory.h"
#include "SimpleSerializable.h"
#include "SimpleConfiguration.h"

using json = nlohmann::json;

class SIMPLE_API SimpleObject :public SimpleFactory<SimpleObject>,
					public SimpleSerializable{

public:

	SimpleObject() :_name("") {};
	virtual void Advance(float dt) = 0;
	virtual void Render(float dt) = 0;

	inline const glm::vec3& GetPosition() const { return _aabb.position; };
	inline const glm::vec2& GetSize() const { return _aabb.size; };
	inline const float& GetOrientation() const { return _orientation; };
	inline const SimpleID& GetName() const { return _name; };
	inline void SetPosition(const glm::vec3&& pos) { _aabb.position = pos; };
	inline void SetPosition(const glm::vec3& pos) { _aabb.position = pos; };
	inline void SetSize(glm::vec2&& size) { _aabb.size = size; };
	inline void SetSize(glm::vec2& size) { _aabb.size = size; };
	inline void SetOrientation(float&& orientation) { _orientation = orientation; };
	inline void SetOrientation(float& orientation) { _orientation = orientation; };
	inline void SetName(SimpleID name) { _name = name; };
	
	inline const SimpleAABB& GetAABB()const { return _aabb; };
	//Not efficient... we could do a lot better
	const glm::mat4 GetTransform() const;
	virtual SimpleID GetType() { return "SimpleObject"; }
	
	json Serialize() override;
	bool Deserialize(const json& node) override;
	

protected:
	SimpleAABB _aabb;
	float _orientation	= 0.0f;
	SimpleID _name;

};
