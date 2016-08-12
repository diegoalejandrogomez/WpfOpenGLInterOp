#pragma once
#include "SimpleTexture.h"
#include "SimpleAABB.h"
#include <stdlib.h>
#include <vector>

class SimpleSpriteSheet : public SimpleTexture{

public:

	SimpleSpriteSheet();
	~SimpleSpriteSheet();

	void CreateUniformFrames(glm::ivec2 size, glm::ivec2 count);
	void AddSpriteFrame(glm::ivec2 position, glm::ivec2 size);
	glm::ivec4 GetCoordsForIndex(int idx);
private:

	//XY contains origin, ZW contains size
	std::vector<glm::ivec4> _frames;

	glm::ivec2 _spriteCellSize;
	glm::ivec2 _spriteCellCount;

};
