#include "stdafx.h"
#include "ISimpleSpriteSheet.h"

extern "C" {

	SIMPLE_API void SimpleSpriteSheet_CreateUniformFrames(SimpleSpriteSheet *sheet, int sizeX, int sizeY, int countX, int countY) {
		sheet->CreateUniformFrames({ sizeX,sizeY }, { countX, countY });
	}
	SIMPLE_API int SimpleSpriteSheet_AddSpriteFrame(SimpleSpriteSheet *sheet, int positionX, int positionY, int sizeX, int sizeY) {
		return sheet->AddSpriteFrame({ positionX, positionY }, { sizeX, sizeY });
	}

	SIMPLE_API int SimpleSpriteSheet_GetFrameIndex(SimpleSpriteSheet *sheet, int positionX, int positionY, int sizeX, int sizeY) {
		return sheet->GetFrameIndex({ positionX, positionY }, { sizeX, sizeY });
	}
	SIMPLE_API void SimpleSpriteSheet_ClearFrames(SimpleSpriteSheet *sheet) {
		sheet->ClearFrames();
	}
	SIMPLE_API void SimpleSpriteSheet_GetCoordsForIndex(SimpleSpriteSheet *sheet, int idx, int &positionX, int& positionY,
		int &sizeX, int &sizeY) {

		glm::ivec4 coords = sheet->GetCoordsForIndex(idx);
		positionX = coords.x;
		positionY = coords.y;
		sizeX = coords.z;
		sizeY = coords.w;

	}
}