#pragma once
#include <tuple>
#include <glm\glm.hpp>

class SimpleObject {

public:

	virtual void Advance(float dt) = 0;
	virtual void Render(float dt) = 0;

	inline const glm::vec3& GetPosition()const { return _position; };
	inline const glm::vec2& GetSize()const { return _size; };
	inline const float& GetOrientation()const { return _orientation; };

	inline void SetPosition(glm::vec3&& pos) { _position = pos; };
	inline void SetSize(glm::vec2&& size) { _size = size; };
	inline void SetOrientation(float&& orientation) { _orientation = orientation; };

protected:

	glm::vec3 _position;
	glm::vec2 _size;
	float _orientation;

};
