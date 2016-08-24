#include "stdafx.h"
#include "ISimpleSpriteRenderer.h"

extern "C" {
	SIMPLE_API SimpleSpriteRenderer* SimpleSpriteRenderer_Create() {

		return new SimpleSpriteRenderer();

	}
	SIMPLE_API void SimpleSpriteRenderer_Destroy(SimpleSpriteRenderer* sprite) {
		delete sprite;
	}

	SIMPLE_API void SimpleSpriteRenderer_SetAsTexture(SimpleSpriteRenderer* sprite, const char* name) {
		sprite->SetAsTexture(name);
	}
	SIMPLE_API void SimpleSpriteRenderer_SetAsTextureRect(SimpleSpriteRenderer* sprite, const char* name, float offsetX, float offsetY,
		float width, float height) {

		sprite->SetAsTextureRect(name, { offsetX, offsetY }, { width, height });

	}

	SIMPLE_API void SimpleSpriteRenderer_SetRect(SimpleSpriteRenderer* sprite, float offsetX, float offsetY, float width, float height) {

		sprite->SetRect({ offsetX, offsetY }, { width, height });

	}
	SIMPLE_API void SimpleSpriteRenderer_SnapToGrid(SimpleSpriteRenderer* sprite, bool snap) {
		sprite->SnapToGrid(snap);

	}
	SIMPLE_API void SimpleSpriteRenderer_SetSnapGridSize(SimpleSpriteRenderer* sprite, float gridWidth, float gridHeight) {

		sprite->SetSnapGridSize({ gridWidth, gridHeight });
	}

	SIMPLE_API SimpleTexture* SimpleSpriteRenderer_GetTexture(SimpleSpriteRenderer* sprite) {

		return sprite->GetTexture();
	}
}