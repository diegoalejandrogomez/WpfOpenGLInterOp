#include "stdafx.h"
#include "SimpleAABB.h"

bool SimpleAABB::Contains(float px, float py) const {

	return ( px > position.x && px < (position.x + size.x) && py > position.y && py < (position.y + size.y) );

}
bool SimpleAABB::Overlaps(const SimpleAABB &other) const {
	
	return ! (	other.position.x > (position.x+size.x) || (other.position.x+other.size.x) < position.x || 
				other.position.y > (position.y+size.y) || (other.position.y+other.size.y) < position.y );
}