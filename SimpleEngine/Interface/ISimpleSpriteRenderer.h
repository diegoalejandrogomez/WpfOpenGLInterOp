#pragma once
#include "SimpleScene.h"
#include "SimpleSpriteRenderer.h"
#include "SimpleConfiguration.h"
#include "SimpleLayer.h"

extern "C" {

	SIMPLE_API SimpleSpriteRenderer* SimpleSpriteRenderer_Create();
	SIMPLE_API void SimpleSpriteRenderer_Destroy(SimpleSpriteRenderer* sprite);
	
	SIMPLE_API void SimpleSpriteRenderer_SetAsTexture(SimpleSpriteRenderer* sprite, const char* name);
	SIMPLE_API void SimpleSpriteRenderer_SetAsTextureRect(SimpleSpriteRenderer* sprite, const char* name, float offsetX, float offsetY,
															float width, float height);
		
	SIMPLE_API void SimpleSpriteRenderer_SetRect(SimpleSpriteRenderer* sprite, float offsetX, float offsetY, float width, float height);
	SIMPLE_API void SimpleSpriteRenderer_SnapToGrid(SimpleSpriteRenderer* sprite, bool snap);
	SIMPLE_API void SimpleSpriteRenderer_SetSnapGridSize(SimpleSpriteRenderer* sprite, float gridWidth, float gridHeight);
	
	SIMPLE_API SimpleTexture* SimpleSpriteRenderer_GetTexture(SimpleSpriteRenderer* sprite);

}