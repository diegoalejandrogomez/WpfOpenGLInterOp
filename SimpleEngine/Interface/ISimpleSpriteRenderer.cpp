#include "stdafx.h"
#include "ISimpleSpriteRenderer.h"

SimpleSpriteRenderer* SimpleSpriteRenderer_Create() {
	
	return new SimpleSpriteRenderer();

}
void SimpleSpriteRenderer_Destroy(SimpleSpriteRenderer* sprite) {
	delete sprite;
}

void SimpleSpriteRenderer_SetAsTexture(SimpleSpriteRenderer* sprite, const char* name) {
	sprite->SetAsTexture(name);
}
void SimpleSpriteRenderer_SetAsTextureRect(SimpleSpriteRenderer* sprite, const char* name, float offsetX, float offsetY,
	float width, float height) {

	sprite->SetAsTextureRect(name, { offsetX, offsetY }, { width, height });

}

void SimpleSpriteRenderer_SetRect(SimpleSpriteRenderer* sprite, float offsetX, float offsetY, float width, float height) {

	sprite->SetRect({ offsetX, offsetY }, { width, height });

}
void SimpleSpriteRenderer_SnapToGrid(SimpleSpriteRenderer* sprite, bool snap) {
	sprite->SnapToGrid(snap);

}
void SimpleSpriteRenderer_SetSnapGridSize(SimpleSpriteRenderer* sprite, float gridWidth, float gridHeight) {

	sprite->SetSnapGridSize({ gridWidth, gridHeight });
}

SimpleTexture* SimpleSpriteRenderer_GetTexture(SimpleSpriteRenderer* sprite) {

	return sprite->GetTexture();
}