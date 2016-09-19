#pragma once
#include <glm\glm.hpp>
class SimpleObject;

struct SimpleContactInfo {
	SimpleObject* other;
	glm::vec2 points[2];
	glm::vec2 normal;
	
};
