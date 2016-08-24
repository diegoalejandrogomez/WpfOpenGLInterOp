#pragma once
#include "SimpleSpriteSheetRenderer.h"
#include "SimpleConfiguration.h"

extern "C" {

	SIMPLE_API SimpleSpriteSheetRenderer* SimpleSpriteSheetRenderer_Create();
	SIMPLE_API void SimpleSpriteSheetRenderer_Destroy(SimpleSpriteSheetRenderer* sprite);

	SIMPLE_API void SimpleSpriteSheetRenderer_SetSpriteSheetWithName(SimpleSpriteSheetRenderer* sprite, const char* sheetName);
	SIMPLE_API void SimpleSpriteSheetRenderer_SetSpriteSheet(SimpleSpriteSheetRenderer* sprite, SimpleSpriteSheet* sheet);

	SIMPLE_API SimpleSpriteSheet* SimpleSpriteSheetRenderer_GetSpriteSheet(SimpleSpriteSheetRenderer* sprite);
	SIMPLE_API void SimpleSpriteSheetRenderer_SetIndex(SimpleSpriteSheetRenderer* sprite, int pos);
	SIMPLE_API int SimpleSpriteSheetRenderer_GetIndex(SimpleSpriteSheetRenderer* sprite);


}

