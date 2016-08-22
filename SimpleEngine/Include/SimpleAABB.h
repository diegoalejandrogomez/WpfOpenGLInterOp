#pragma once
#include "SimpleConfiguration.h"



//A 2D aabb living in a 3D world
struct SIMPLE_API SimpleAABB {

	glm::vec3 position = glm::vec3(0.0f);
	glm::vec2 size = glm::vec2(0.0f);
	
	SimpleAABB() {}
	SimpleAABB(glm::vec2 lowerLeft, glm::vec2 upperRight) {
		position.x = (upperRight.x + lowerLeft.x) * 0.5f;
		position.y = (upperRight.y + lowerLeft.y) * 0.5f;
		position.z = 0.0f ;
		size = (upperRight - lowerLeft);
	}

	bool Contains(float px, float py) const;
	bool Overlaps(const SimpleAABB &other) const;

	//Ok, we should have this in a separate class, but will keep them here for now... collision check using transformed AABB
	bool Contains(const glm::mat4& transform, float px, float py) const;
	bool Overlaps(const glm::mat4& transform, const SimpleAABB &other, const glm::mat4& otherTransform) const;
};
