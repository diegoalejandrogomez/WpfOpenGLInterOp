#pragma once
#include "SimpleTexture.h"
#include "SimpleAABB.h"

class SimpleSpriteSheet : public SimpleTexture{

public:

	SimpleSpriteSheet();
	~SimpleSpriteSheet();

	inline void SetCellSize(glm::ivec2& size) { _spriteCellSize = size; };
	inline void SetCellSize(glm::ivec2&& size) { _spriteCellSize = size; };
	inline void SetCellCount(glm::ivec2& count) { _spriteCellCount = count; };
	inline void SetCellCount(glm::ivec2&& count) { _spriteCellCount = count; };
	
	inline glm::ivec2 GetCellSize() { return _spriteCellSize; }
	inline glm::ivec2 GetCellCount() { return _spriteCellCount; }

	
	SimpleAABB GetUVForIndex(glm::vec2 idxs);
	glm::ivec4 GetCoordsForIndex(glm::vec2 idxs);
private:

	glm::ivec2 _spriteCellSize;
	glm::ivec2 _spriteCellCount;

};
