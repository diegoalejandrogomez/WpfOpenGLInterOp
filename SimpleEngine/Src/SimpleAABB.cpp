#include "stdafx.h"
#include "SimpleAABB.h"
#include <algorithm>

bool SimpleAABB::Contains(float px, float py) const {
	glm::vec3 ll= LowerLeft();
	glm::vec3 ur = UpperRight();
	return ( px > (ll.x)  && px < (ur.x) && py > (ll.y) && py < (ur.y) );

}
bool SimpleAABB::Overlaps(const SimpleAABB &other) const {
	glm::vec3 ll = LowerLeft();
	glm::vec3 ur = UpperRight();

	glm::vec3 oll = LowerLeft();
	glm::vec3 our = UpperRight();

	glm::vec2 halfSize = size * 0.5f;
	glm::vec2 otherHalfSize = other.size * 0.5f;
	return ! (	(oll.x > ur.x) || (our.x < ll.x)|| 
				(oll.y > ur.y) || (our.y < ll.y ));
}


bool SimpleAABB::Contains(const glm::mat4& transform, float px, float py) const {
	//Transform the point to the local AABB coordinate system
	glm::vec4 localP = glm::inverse(transform) * glm::vec4{ px, py, 0.0f,1.0f };
	glm::vec3 ll = LowerLeft() - position; //Not scaled nor rotated
	glm::vec3 ur = UpperRight() - position;
	
	return (localP.x > ll.x && localP.x <  ur.x && localP.y > ll.y  && localP.y < ur.y);

}
bool SimpleAABB::Overlaps(const glm::mat4& transform, const SimpleAABB &other, const glm::mat4& otherTransform) const {
	//Ad hoc SAT. Transform other to local coordinate system and check both axis
	glm::vec3 ll = LowerLeft() - position;
	glm::vec3 ur = UpperRight() - position;

	glm::vec3 oll = other.LowerLeft();
	glm::vec3 our = other.UpperRight();

	glm::mat4 acumTransform = glm::inverse(transform) * otherTransform;

	glm::vec4 lowerLeft = acumTransform *  glm::vec4{	oll.x, oll.y , 0.0f, 1.0f };
	glm::vec4 upperRight = acumTransform *  glm::vec4{ our.x, our.y, 0.0f, 1.0f };
	
	//Should project
	return !(	(std::max(lowerLeft.x, upperRight.x) < ll.x) || (std::min(lowerLeft.x, upperRight.x) > ur.x) ||
				(std::max(lowerLeft.y, upperRight.y) < ll.y) || (std::min(lowerLeft.y, upperRight.y) > ur.y)
			);
	


}