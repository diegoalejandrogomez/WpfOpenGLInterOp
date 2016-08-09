#include "stdafx.h"
#include "SimpleAABB.h"

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