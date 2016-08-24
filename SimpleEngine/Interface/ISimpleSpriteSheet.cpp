#include "stdafx.h"
#include "ISimpleSpriteSheet.h"


void SimpleSpriteSheet_CreateUniformFrames(SimpleSpriteSheet *sheet, int sizeX, int sizeY, int countX, int countY) {
	sheet->CreateUniformFrames({ sizeX,sizeY }, { countX, countY });
}
int SimpleSpriteSheet_AddSpriteFrame(SimpleSpriteSheet *sheet, int positionX, int positionY, int sizeX, int sizeY) {
	return sheet->AddSpriteFrame({ positionX, positionY }, { sizeX, sizeY });
}

int SimpleSpriteSheet_GetFrameIndex(SimpleSpriteSheet *sheet, int positionX, int positionY, int sizeX, int sizeY) {
	return sheet->GetFrameIndex({ positionX, positionY }, { sizeX, sizeY });
}
void SimpleSpriteSheet_ClearFrames(SimpleSpriteSheet *sheet) {
	sheet->ClearFrames();
}
void SimpleSpriteSheet_GetCoordsForIndex(SimpleSpriteSheet *sheet, int idx, int &positionX, int& positionY,
	int &sizeX, int &sizeY) {
	
	glm::ivec4 coords = sheet->GetCoordsForIndex(idx);
	positionX = coords.x;
	positionY = coords.y;
	sizeX = coords.z;
	sizeY = coords.w;

}