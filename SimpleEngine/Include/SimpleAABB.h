#pragma once

//A 2D aabb living in a 3D world
struct SimpleAABB {
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec2 size = glm::vec2(0.0f);

	bool Contains(float px, float py) const;
	bool Overlaps(const SimpleAABB &other) const;

	//Ok, we should have this in a separate class, but will keep them here for now... collision check using transformed AABB
	bool Contains(const glm::mat4& transform, float px, float py) const;
	bool Overlaps(const glm::mat4& transform, const SimpleAABB &other, const glm::mat4& otherTransform) const;
};
