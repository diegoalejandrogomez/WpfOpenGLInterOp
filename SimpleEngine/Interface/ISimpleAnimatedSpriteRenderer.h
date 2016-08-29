#pragma once
#include "SimpleAnimatedSpriteRenderer.h"
#include "SimpleConfiguration.h"

extern "C" {

	SIMPLE_API SimpleAnimatedSpriteRenderer* SimpleAnimatedSpriteRenderer_Create();
	SIMPLE_API void SimpleAnimatedSpriteRenderer_Destroy(SimpleAnimatedSpriteRenderer* sprite);
	SIMPLE_API void SimpleAnimatedSpriteRenderer_SetAnimation(SimpleAnimatedSpriteRenderer* sprite, SimpleSpriteAnimation* anim);
	SIMPLE_API void SimpleAnimatedSpriteRenderer_SetAnimationWithName(SimpleAnimatedSpriteRenderer* sprite, const char* anim);

	SIMPLE_API void SimpleAnimatedSpriteRenderer_Play(SimpleAnimatedSpriteRenderer* sprite);
	SIMPLE_API void SimpleAnimatedSpriteRenderer_PlayOnce(SimpleAnimatedSpriteRenderer* sprite);
	SIMPLE_API void SimpleAnimatedSpriteRenderer_Stop(SimpleAnimatedSpriteRenderer* sprite);
	SIMPLE_API void SimpleAnimatedSpriteRenderer_Pause(SimpleAnimatedSpriteRenderer* sprite);


}