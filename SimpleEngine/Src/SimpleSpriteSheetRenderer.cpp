#include "stdafx.h"
#include "SimpleSpriteSheetRenderer.h"
#include "SimpleEngine.h"
#include <algorithm>
#include <glm\gtx\transform.hpp>
#include "SimpleEngine.h"
#include "SimpleRenderer.h"
#include "SimpleTexture.h"

SimpleSpriteSheetRenderer::SimpleSpriteSheetRenderer() {
	_xPos = 0;
	_yPos = 0;
}

SimpleSpriteSheetRenderer::~SimpleSpriteSheetRenderer() {


}

void SimpleSpriteSheetRenderer::SetSpriteSheet(std::string sheetName){

	_spriteSheet = SimpleEngine::Instance()->GetRenderer()->GetSpriteSheet(sheetName);

}

void SimpleSpriteSheetRenderer::SetSpriteSheet(SimpleSpriteSheet* sheet) {

	_spriteSheet = sheet;

}

void SimpleSpriteSheetRenderer::Advance(float dt) {
	
	
	//Not useful for now... but just in case
	SimpleSpriteRenderer::Advance(dt);

}

void SimpleSpriteSheetRenderer::SetIndex(int x, int y){
	_xPos = x;
	_yPos = y;
}

void SimpleSpriteSheetRenderer::Render(float dt) {
	
	//Pick cell to render from sprite source
	glm::vec4 frame = _spriteSheet->GetCoordsForIndex({ _xPos, _yPos });
	SimpleTexture *t = static_cast<SimpleTexture*>(_spriteSheet);
	SetAsTextureRect(t, glm::vec2{ frame.x, frame.y }, glm::vec2{ frame.z, frame.w });
	SimpleSpriteRenderer::Render(dt);


}


