#include "stdafx.h"
#include "ISimpleSpriteAnimation.h"

extern "C" {

	SIMPLE_API SimpleSpriteAnimation* SimpleSpriteAnimation_Create() {
		return new SimpleSpriteAnimation();
	}
	SIMPLE_API void SimpleSpriteAnimation__Destroy(SimpleSpriteAnimation* sprite) {
		delete sprite;
	}

	SIMPLE_API void SimpleSpriteAnimation_SetAnimationName(SimpleSpriteAnimation* sprite, const char* name) {
		sprite->SetAnimationName(name);
	}
	SIMPLE_API void SimpleSpriteAnimation_SetSpriteSheet(SimpleSpriteAnimation* sprite, SimpleSpriteSheet* sheet) {
		sprite->SetSpriteSheet(sheet);
	}

	SIMPLE_API void SimpleSpriteAnimation_SetSpriteSheetWithName(SimpleSpriteAnimation* sprite, const char*  sheetName) {
		sprite->SetSpriteSheet(sheetName);
	}

	SIMPLE_API void SimpleSpriteAnimation_SetFrames(SimpleSpriteAnimation* sprite, const int* frames, int amount) {
		std::vector<int> vframes;
		vframes.assign(frames, frames + amount);
		sprite->SetFrames(vframes);
	}

	SIMPLE_API void SimpleSpriteAnimation_AddFrame(SimpleSpriteAnimation* sprite, int idx) {
		sprite->AddFrame(idx);
	}

	SIMPLE_API void SimpleSpriteAnimation_ClearFrames(SimpleSpriteAnimation* sprite) {
		sprite->ClearFrames();
	}

	SIMPLE_API void SimpleSpriteAnimation_SetFrameTime(SimpleSpriteAnimation* sprite, float frameTime) {
		sprite->SetFrameTime(frameTime);
	}

	SIMPLE_API const float SimpleSpriteAnimation_GetFrameTime(SimpleSpriteAnimation* sprite) {
		return sprite->GetFrameTime();
	}
	
	SIMPLE_API const int SimpleSpriteAnimation_GetFrameCount(SimpleSpriteAnimation* sprite) {
		return sprite->GetFrameCount();
	}
	
	SIMPLE_API const int SimpleSpriteAnimation_GetFrame(SimpleSpriteAnimation* sprite, int n) {
		return sprite->GetFrame(n);
	}
	
	SIMPLE_API SimpleSpriteSheet* SimpleSpriteAnimation_GetSpriteSheet(SimpleSpriteAnimation* sprite) {
		return sprite->GetSpriteSheet();
	}
	
	SIMPLE_API const char* SimpleSpriteAnimation_GetAnimationName(SimpleSpriteAnimation* sprite) {
		return sprite->GetAnimationName().c_str();
	}

}
