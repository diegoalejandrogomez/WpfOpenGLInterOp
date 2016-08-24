#include "stdafx.h"
#include "ISimpleSpriteSheetRenderer.h"


SimpleSpriteSheetRenderer* SimpleSpriteSheetRenderer_Create() {
	return new SimpleSpriteSheetRenderer();
}
void SimpleSpriteSheetRenderer_Destroy(SimpleSpriteSheetRenderer* sprite) {
	delete sprite;
}
void SimpleSpriteSheetRenderer_SetSpriteSheetWithName(SimpleSpriteSheetRenderer* sprite, const char* sheetName) {
	sprite->SetSpriteSheet(sheetName);
}
void SimpleSpriteSheetRenderer_SetSpriteSheet(SimpleSpriteSheetRenderer* sprite, SimpleSpriteSheet* sheet) {
	sprite->SetSpriteSheet(sheet);
}

SimpleSpriteSheet* SimpleSpriteSheetRenderer_GetSpriteSheet(SimpleSpriteSheetRenderer* sprite) {
	return sprite->GetSpriteSheet();
}

void SimpleSpriteSheetRenderer_SetIndex(SimpleSpriteSheetRenderer* sprite, int pos) {
	sprite->SetIndex(pos);
}

int SimpleSpriteSheetRenderer_GetIndex(SimpleSpriteSheetRenderer* sprite) {

	return sprite->GetIndex();
}