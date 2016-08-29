#pragma once
#include "SimpleSpriteAnimation.h"
#include "SimpleConfiguration.h"

extern "C" {

	SIMPLE_API SimpleSpriteAnimation* SimpleSpriteAnimation_Create();
	SIMPLE_API void SimpleSpriteAnimation_Destroy(SimpleSpriteAnimation* sprite);

	SIMPLE_API void SimpleSpriteAnimation_SetAnimationName(SimpleSpriteAnimation* sprite, const char* name);
	SIMPLE_API void SimpleSpriteAnimation_SetSpriteSheet(SimpleSpriteAnimation* sprite, SimpleSpriteSheet* sheet);
	SIMPLE_API void SimpleSpriteAnimation_SetSpriteSheetWithName(SimpleSpriteAnimation* sprite, const char*  sheetName);
	SIMPLE_API void SetFrames(SimpleSpriteAnimation* sprite, const int* frames, int amount);
	SIMPLE_API void SimpleSpriteAnimation_AddFrame(SimpleSpriteAnimation* sprite, int idx);
	SIMPLE_API void SimpleSpriteAnimation_ClearFrames(SimpleSpriteAnimation* sprite);
	SIMPLE_API void SimpleSpriteAnimation_SetFrameTime(SimpleSpriteAnimation* sprite, float frameTime);

	SIMPLE_API const float SimpleSpriteAnimation_GetFrameTime(SimpleSpriteAnimation* sprite);
	SIMPLE_API const int SimpleSpriteAnimation_GetFrameCount(SimpleSpriteAnimation* sprite);
	SIMPLE_API const int SimpleSpriteAnimation_GetFrame(SimpleSpriteAnimation* sprite,int n);
	SIMPLE_API SimpleSpriteSheet* SimpleSpriteAnimation_GetSpriteSheet(SimpleSpriteAnimation* sprite);
	SIMPLE_API const char* SimpleSpriteAnimation_GetAnimationName(SimpleSpriteAnimation* sprite);

}

