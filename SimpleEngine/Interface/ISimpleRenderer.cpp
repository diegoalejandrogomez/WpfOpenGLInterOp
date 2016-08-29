#include "stdafx.h"
#include "SimpleRenderer.h"
#include "SimpleConfiguration.h"
#include "SimpleEngine.h"

extern "C" {
	SIMPLE_API void SimpleRenderer_ResizeWindow(int width, int height) {
		SimpleEngine::Instance()->GetRenderer()->ResizeWindow(width, height);
	}

	SIMPLE_API int SimpleRenderer_GetWidth() {
		return SimpleEngine::Instance()->GetRenderer()->GetWidth();
	};

	SIMPLE_API int SimpleRenderer_GetHeight() {
		return SimpleEngine::Instance()->GetRenderer()->GetHeight();
	};

	SIMPLE_API bool SimpleRenderer_CreateSpriteSheet(const char* texturePath, int frameSizeX, int frameSizeY, int frameCountX, int frameCountY) {
		return SimpleEngine::Instance()->GetRenderer()->CreateSpriteSheet(texturePath, { frameSizeX, frameSizeY },
		{ frameCountX, frameCountY });
	}

	SIMPLE_API bool SimpleRenderer_CreateSpriteSheetEmpty(const char* texturePath) {
		return SimpleEngine::Instance()->GetRenderer()->CreateSpriteSheet(texturePath);
	}

	SIMPLE_API SimpleSpriteSheet* SimpleRenderer_GetSpriteSheet(const char* texturePath) {
		return SimpleEngine::Instance()->GetRenderer()->GetSpriteSheet(texturePath);
	}

	SIMPLE_API bool SimpleRenderer_CreateSpriteAnimation(const char* name, const char* spriteSheet, int* frames, int frameCount, float frameTime) {
		return SimpleEngine::Instance()->GetRenderer()->CreateSpriteAnimation(name, spriteSheet, std::vector<int>(frames[0], frames[frameCount - 1]), frameTime);
	}

	SIMPLE_API bool Simplerenderer_CreateSpriteAnimationEmpty(const char* name) {
		return SimpleEngine::Instance()->GetRenderer()->CreateSpriteAnimation(name);
	}

	SIMPLE_API SimpleSpriteAnimation* SimpleRenderer_GetSpriteAnimation(const char* name) {
		return SimpleEngine::Instance()->GetRenderer()->GetSpriteAnimation(name);
	}


}