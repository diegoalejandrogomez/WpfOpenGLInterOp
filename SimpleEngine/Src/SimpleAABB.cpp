#include "stdafx.h"
#include "SimpleAABB.h"
#include <algorithm>

bool SimpleAABB::Contains(float px, float py) const {
	glm::vec2 halfSize= size * 0.5f;
	return ( px > (position.x-halfSize.x)  && px < (position.x + halfSize.x) && py > (position.y-halfSize.y) && py < (position.y + halfSize.y) );

}
bool SimpleAABB::Overlaps(const SimpleAABB &other) const {
	glm::vec2 halfSize = size * 0.5f;
	glm::vec2 otherHalfSize = other.size * 0.5f;
	return ! (	(other.position.x-otherHalfSize.x) > (position.x+halfSize.x) || (other.position.x+otherHalfSize.x) < (position.x - halfSize.x)|| 
				(other.position.y - otherHalfSize.y) > (position.y+halfSize.y) || (other.position.y+otherHalfSize.y) < (position.y - halfSize.y) );
}


bool SimpleAABB::Contains(const glm::mat4& transform, float px, float py) const {
	//Transform the point to the local AABB coordinate system
	glm::vec4 localP = glm::inverse(transform) * glm::vec4{ px, py, 0.0f,1.0f };
	glm::vec2 halfSize = size * 0.5f;
	return (localP.x > (-halfSize.x) && localP.x < ( halfSize.x) && localP.y >( - halfSize.y) && localP.y < (halfSize.y));

}
bool SimpleAABB::Overlaps(const glm::mat4& transform, const SimpleAABB &other, const glm::mat4& otherTransform) const {
	//Ad hoc SAT. Transform other to local coordinate system and check both axis
	glm::mat4 acumTransform = glm::inverse(transform) * otherTransform;

	glm::vec4 lowerLeft = acumTransform *  glm::vec4{	other.position.x - other.size.x * 0.5f, 
													other.position.y - other.size.y * 0.5f, 0.0f, 1.0f };
	glm::vec4 upperRight = acumTransform *  glm::vec4{ other.position.x + other.size.x * 0.5f,
													other.position.y + other.size.y * 0.5f, 0.0f, 1.0f };
	glm::vec2 halfSize = size * 0.5f;
	//Should project
	return !(	(std::min(lowerLeft.x, upperRight.x) < -halfSize.x) || (std::max(lowerLeft.x, upperRight.x) > halfSize.x) ||
				(std::min(lowerLeft.y, upperRight.y) < -halfSize.y) || (std::max(lowerLeft.y, upperRight.y) > halfSize.y)
			);
	


}