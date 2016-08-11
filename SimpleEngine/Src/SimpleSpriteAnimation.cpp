#include "stdafx.h"
#include "SimpleSpriteAnimation.h"
#include "SimpleEngine.h"
#include "SimpleRenderer.h"


void SimpleSpriteAnimation::SetSpriteSheet(const std::string sheetName) {
	_sheet = SimpleEngine::Instance()->GetRenderer()->GetSpriteSheet(sheetName);
	SIMPLE_ASSERT(_sheet != nullptr);
}

void SimpleSpriteAnimation::SetSpriteSheet(SimpleSpriteSheet* sheet) {
	_sheet = sheet;
}