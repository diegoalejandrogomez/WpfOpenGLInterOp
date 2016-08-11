#include "stdafx.h"
#include "SimpleSpriteSheet.h"
#include "SimpleAABB.h"

SimpleSpriteSheet::SimpleSpriteSheet() {

}
SimpleSpriteSheet::~SimpleSpriteSheet() {

}

//Returns an AABB with anchor point in lower left corner of texture
SimpleAABB SimpleSpriteSheet::GetUVForIndex(glm::vec2 idxs) {

	SIMPLE_ASSERT(idxs.x < _spriteCellCount.x && idxs.y < _spriteCellCount.y);

	//Return the pixel coordinates for the current sheet
	SimpleAABB aabb;
	aabb.position.x = idxs.x * _spriteCellSize.x / (float)GetPOTWidth();
	aabb.position.y = idxs.y * _spriteCellSize.y / (float) GetPOTHeight();
	aabb.size.x = GetWidth() /  (float)_spriteCellCount.x / (float)GetPOTWidth();
	aabb.size.y = GetHeight() / (float)_spriteCellCount.y / (float)GetPOTHeight();
	return aabb;

}

glm::ivec4 SimpleSpriteSheet::GetCoordsForIndex(glm::vec2 idxs) {

	SIMPLE_ASSERT(idxs.x < _spriteCellCount.x && idxs.y < _spriteCellCount.y);

	//Return the pixel coordinates for the current sheet
	glm::ivec4 coords;
	//XY
	coords.x = idxs.x * _spriteCellSize.x;
	coords.y = GetHeight() - (idxs.y+1) * _spriteCellSize.y;
	//SIZE
	coords.z = _spriteCellSize.x ;
	coords.w = _spriteCellSize.y ;
	return coords;

}
