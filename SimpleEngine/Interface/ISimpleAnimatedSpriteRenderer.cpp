#include "stdafx.h"
#include "ISimpleAnimatedSpriteRenderer.h"

extern "C" {

	SIMPLE_API SimpleAnimatedSpriteRenderer* SimpleAnimatedSpriteRenderer_Create() {
		return new SimpleAnimatedSpriteRenderer();
	}

	SIMPLE_API void SimpleAnimatedSpriteRenderer_Destroy(SimpleAnimatedSpriteRenderer *sprite) {
		delete sprite;
	}
	SIMPLE_API void SimpleAnimatedSpriteRenderer_SetAnimation(SimpleAnimatedSpriteRenderer* sprite, SimpleSpriteAnimation* anim) {
		sprite->SetAnimation(anim);
	}
	SIMPLE_API void SimpleAnimatedSpriteRenderer_SetAnimationWithName(SimpleAnimatedSpriteRenderer* sprite, const char* anim) {
		sprite->SetAnimation(anim);
	}

	SIMPLE_API void SimpleAnimatedSpriteRenderer_Play(SimpleAnimatedSpriteRenderer* sprite) {
		sprite->Play();
	}
	SIMPLE_API void SimpleAnimatedSpriteRenderer_PlayOnce(SimpleAnimatedSpriteRenderer* sprite) {
		sprite->PlayOnce();
	}
	SIMPLE_API void SimpleAnimatedSpriteRenderer_Stop(SimpleAnimatedSpriteRenderer* sprite) {
		sprite->Stop();
	}
	SIMPLE_API void SimpleAnimatedSpriteRenderer_Pause(SimpleAnimatedSpriteRenderer* sprite) {
		sprite->Pause();
	}


}