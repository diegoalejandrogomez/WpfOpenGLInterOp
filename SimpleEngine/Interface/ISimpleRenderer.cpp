#include "stdafx.h"
#include "SimpleRenderer.h"
#include "SimpleConfiguration.h"
#include "SimpleEngine.h"


void SimpleRenderer_ResizeWindow(int width, int height) {
	SimpleEngine::Instance()->GetRenderer()->ResizeWindow(width, height);
}
	
int SimpleRenderer_GetWidth(){
	return SimpleEngine::Instance()->GetRenderer()->GetWidth();
};

int SimpleRenderer_GetHeight(){
	return SimpleEngine::Instance()->GetRenderer()->GetHeight();
};
		
bool SimpleRenderer_CreateSpriteSheet(const char* texturePath, int* frameSize, int* frameCount) {
	return SimpleEngine::Instance()->GetRenderer()->CreateSpriteSheet(	texturePath, { frameSize[0], frameSize[1] },
																			{ frameCount[0], frameCount[1] });
}

bool SimpleRenderer_CreateSpriteSheetEmpty(const char* texturePath) {
		return SimpleEngine::Instance()->GetRenderer()->CreateSpriteSheet(texturePath);
}

SimpleSpriteSheet* SimpleEngine_GetSpriteSheet(const char* texturePath) {
		return SimpleEngine::Instance()->GetRenderer()->GetSpriteSheet(texturePath);
}

bool SimpleRenderer_CreateSpriteAnimation(const char* name, const char* spriteSheet, int* frames, int frameCount, float frameTime) {
		return SimpleEngine::Instance()->GetRenderer()->CreateSpriteAnimation(name, spriteSheet, std::vector<int>(frames[0], frames[frameCount - 1]), frameTime);
}

SimpleSpriteAnimation* SimpleRenderer_GetSpriteAnimation(const char* name) {
		return SimpleEngine::Instance()->GetRenderer()->GetSpriteAnimation(name);
}



