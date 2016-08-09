#pragma once

//A 2D aabb living in a 3D world
struct SimpleAABB {
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec2 size = glm::vec2(0.0f);

	bool Contains(float px, float py) const;
	bool Overlaps(const SimpleAABB &other) const;
};
