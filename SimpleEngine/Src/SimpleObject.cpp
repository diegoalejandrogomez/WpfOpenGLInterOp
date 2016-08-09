#include "stdafx.h"
#include "SimpleObject.h"
#include <glm\gtx\transform.hpp>

const glm::mat4 SimpleObject::GetTransform()const {
	//We don't have scale for now...
	return  glm::translate(_aabb.position) * glm::rotate(_orientation, glm::vec3(0.0f, 0.0f, 1.0f));

}