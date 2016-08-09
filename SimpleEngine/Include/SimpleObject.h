#pragma once
#include <tuple>
#include <glm\glm.hpp>
#include "SimpleAABB.h"

class SimpleObject {

public:

	virtual void Advance(float dt) = 0;
	virtual void Render(float dt) = 0;

	inline const glm::vec3& GetPosition()const { return _aabb.position; };
	inline const glm::vec2& GetSize()const { return _aabb.size; };
	inline const float& GetOrientation()const { return _orientation; };

	inline void SetPosition(glm::vec3&& pos) { _aabb.position = pos; };
	inline void SetSize(glm::vec2&& size) { _aabb.size = size; };
	inline void SetOrientation(float&& orientation) { _orientation = orientation; };
	inline const SimpleAABB& GetAABB()const { return _aabb; };

protected:
	SimpleAABB _aabb;
	float _orientation	= 0.0f;

};
