#include "stdafx.h"
#include "ISimpleSpriteSheetRenderer.h"

extern "C" {
	SIMPLE_API SimpleSpriteSheetRenderer* SimpleSpriteSheetRenderer_Create() {
		return new SimpleSpriteSheetRenderer();
	}
	SIMPLE_API void SimpleSpriteSheetRenderer_Destroy(SimpleSpriteSheetRenderer* sprite) {
		delete sprite;
	}
	SIMPLE_API void SimpleSpriteSheetRenderer_SetSpriteSheetWithName(SimpleSpriteSheetRenderer* sprite, const char* sheetName) {
		sprite->SetSpriteSheet(sheetName);
	}
	SIMPLE_API void SimpleSpriteSheetRenderer_SetSpriteSheet(SimpleSpriteSheetRenderer* sprite, SimpleSpriteSheet* sheet) {
		sprite->SetSpriteSheet(sheet);
	}

	SIMPLE_API SimpleSpriteSheet* SimpleSpriteSheetRenderer_GetSpriteSheet(SimpleSpriteSheetRenderer* sprite) {
		return sprite->GetSpriteSheet();
	}

	SIMPLE_API void SimpleSpriteSheetRenderer_SetIndex(SimpleSpriteSheetRenderer* sprite, int pos) {
		sprite->SetIndex(pos);
	}

	SIMPLE_API int SimpleSpriteSheetRenderer_GetIndex(SimpleSpriteSheetRenderer* sprite) {

		return sprite->GetIndex();
	}
}