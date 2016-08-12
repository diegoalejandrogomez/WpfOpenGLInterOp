#include "stdafx.h"
#include "SimpleSpriteSheet.h"
#include "SimpleAABB.h"

SimpleSpriteSheet::SimpleSpriteSheet() {

}
SimpleSpriteSheet::~SimpleSpriteSheet() {

}

int SimpleSpriteSheet::AddSpriteFrame(glm::ivec2 position, glm::ivec2 size) {
	
	_frames.emplace_back(position.x, position.y, size.x, size.y);
	return _frames.size()-1;
}


int SimpleSpriteSheet::GetFrameIndex(glm::ivec2 position, glm::ivec2 size) {

	for (int i = 0; i < _frames.size(); ++i)
		if (_frames[i] == glm::ivec4{ position.x, position.y, size.x, size.y })
			return i;
	return -1;	
}

void SimpleSpriteSheet::CreateUniformFrames(glm::ivec2 size, glm::ivec2 count) {

	for (int i = 0;i < count.y; ++i) 
		for (int j = 0; j < count.x; ++j)
			_frames.emplace_back(j*size.x, GetHeight() - (i+1)*size.y, size.x, size.y);
}


glm::ivec4 SimpleSpriteSheet::GetCoordsForIndex(int idx) {

	SIMPLE_ASSERT(idx < _spriteCellCount.x * _spriteCellCount.y);

	//Return the pixel coordinates for the current sheet
	return _frames[idx];
}

