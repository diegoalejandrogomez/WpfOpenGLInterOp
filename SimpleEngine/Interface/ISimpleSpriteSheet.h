#pragma once
#include "SimpleSpriteSheet.h"
#include "SimpleConfiguration.h"

extern "C" {

	SIMPLE_API void SimpleSpriteSheet_CreateUniformFrames(SimpleSpriteSheet *sheet, int sizeX, int sizeY, int countX, int countY);
	SIMPLE_API int SimpleSpriteSheet_AddSpriteFrame(SimpleSpriteSheet *sheet, int positionX, int positionY, int sizeX, int sizeY);
	SIMPLE_API int SimpleSpriteSheet_GetFrameIndex(SimpleSpriteSheet *sheet, int positionX, int positionY, int sizeX, int sizeY);
	SIMPLE_API void SimpleSpriteSheet_ClearFrames(SimpleSpriteSheet *sheet);
	SIMPLE_API void SimpleSpriteSheet_GetCoordsForIndex(SimpleSpriteSheet *sheet, int idx, int &positionX, int& positionY,
											int &sizeX, int &sizeY);
}
