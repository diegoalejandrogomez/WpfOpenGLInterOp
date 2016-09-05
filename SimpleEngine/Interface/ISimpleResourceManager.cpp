#include "stdafx.h"
#include "ISimpleResourceManager.h"

extern "C" {

	SIMPLE_API bool SimpleResourceManager_CreateSpriteSheet(const char* texturePath, int frameSizeX, int frameSizeY, int frameCountX, int frameCountY) {
		return SimpleEngine::Instance()->GetResourceManager()->CreateSpriteSheet(texturePath, { frameSizeX, frameSizeY },
		{ frameCountX, frameCountY });
	}

	SIMPLE_API bool SimpleResourceManager_CreateSpriteSheetEmpty(const char* texturePath) {
		return SimpleEngine::Instance()->GetResourceManager()->CreateSpriteSheet(texturePath);
	}

	SIMPLE_API SimpleSpriteSheet* SimpleResourceManager_GetSpriteSheet(const char* texturePath) {
		return SimpleEngine::Instance()->GetResourceManager()->GetSpriteSheet(texturePath);
	}

	SIMPLE_API bool SimpleResourceManager_CreateSpriteAnimation(const char* name, const char* spriteSheet, int* frames, int frameCount, float frameTime) {
		return SimpleEngine::Instance()->GetResourceManager()->CreateSpriteAnimation(name, spriteSheet, std::vector<int>(frames[0], frames[frameCount - 1]), frameTime);
	}

	SIMPLE_API bool SimpleResourceManager_CreateSpriteAnimationEmpty(const char* name) {
		return SimpleEngine::Instance()->GetResourceManager()->CreateSpriteAnimation(name);
	}

	SIMPLE_API SimpleSpriteAnimation* SimpleResourceManager_GetSpriteAnimation(const char* name) {
		return SimpleEngine::Instance()->GetResourceManager()->GetSpriteAnimation(name);
	}


}