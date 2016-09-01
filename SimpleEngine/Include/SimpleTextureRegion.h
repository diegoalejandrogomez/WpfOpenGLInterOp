#pragma once
#include "SimpleConfiguration.h"

struct SimpleTextureRegion {
	glm::ivec2 lowerLeft;
	glm::ivec2 upperRight;
 	
	uint32_t Width() const{ return upperRight.x - lowerLeft.x + 1; }
	uint32_t Height() const{ return upperRight.y - lowerLeft.y + 1; }
};
