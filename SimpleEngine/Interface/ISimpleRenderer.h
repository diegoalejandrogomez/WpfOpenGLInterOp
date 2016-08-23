#pragma once


#include "stdafx.h"
#include "SimpleRenderer.h"
#include "SimpleConfiguration.h"
#include "SimpleEngine.h"

extern "C" {

	SIMPLE_API void SimpleRenderer_ResizeWindow(int width, int height);

	SIMPLE_API int SimpleRenderer_GetWidth();

	SIMPLE_API int SimpleRenderer_GetHeight();

	SIMPLE_API bool SimpleRenderer_CreateSpriteSheet(const char* texturePath, int* frameSize, int* frameCount);

	SIMPLE_API bool SimpleRenderer_CreateSpriteSheetEmpty(const char* texturePath);

	SIMPLE_API SimpleSpriteSheet* SimpleEngine_GetSpriteSheet(const char* texturePath);

	SIMPLE_API bool SimpleRenderer_CreateSpriteAnimation(const char* name, const char* spriteSheet, int* frames, int frameCount, float frameTime);

	SIMPLE_API SimpleSpriteAnimation* SimpleRenderer_GetSpriteAnimation(const char* name);


}