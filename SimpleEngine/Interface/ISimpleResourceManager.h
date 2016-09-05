#include "SimpleRenderer.h"
#include "SimpleConfiguration.h"
#include "SimpleEngine.h"

extern "C" {
	
	SIMPLE_API bool SimpleResourceManager_CreateSpriteSheet(const char* texturePath, int frameSizeX, int frameSizeY, int frameCountX, int frameCountY);
	SIMPLE_API bool SimpleResourceManager_CreateSpriteSheetEmpty(const char* texturePath);
	SIMPLE_API SimpleSpriteSheet* SimpleResourceManager_GetSpriteSheet(const char* texturePath);
	SIMPLE_API bool SimpleResourceManager_CreateSpriteAnimation(const char* name, const char* spriteSheet, int* frames, int frameCount, float frameTime);
	SIMPLE_API bool SimpleResourceManager_CreateSpriteAnimationEmpty(const char* name);
	SIMPLE_API SimpleSpriteAnimation* SimpleResourceManager_GetSpriteAnimation(const char* name);

	SIMPLE_API void SimpleResourceManager_ClearResources();
	SIMPLE_API bool SimpleResourceManager_SerializeResources(const char* dir);
	SIMPLE_API bool SimpleResourceManager_DeserializeResources(const char *dir);
	SIMPLE_API void SimpleResourceManager_ExportResources(const char* exportPath);
	SIMPLE_API void SImpleResourceManager_ImportResources(const char* exportPath);
}