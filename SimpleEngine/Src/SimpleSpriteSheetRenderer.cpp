#include "stdafx.h"
#include "SimpleSpriteSheetRenderer.h"
#include "SimpleEngine.h"
#include <algorithm>
#include <glm\gtx\transform.hpp>
#include "SimpleEngine.h"
#include "SimpleRenderer.h"
#include "SimpleTexture.h"

SimpleSpriteSheetRenderer::SimpleSpriteSheetRenderer() {
	_pos = 0;
}

SimpleSpriteSheetRenderer::~SimpleSpriteSheetRenderer() {


}

void SimpleSpriteSheetRenderer::SetSpriteSheet(SimpleID sheetName){

	_spriteSheet = SimpleEngine::Instance()->GetRenderer()->GetSpriteSheet(sheetName);
	_UpdateFrame();
}

void SimpleSpriteSheetRenderer::SetSpriteSheet(SimpleSpriteSheet* sheet) {

	_spriteSheet = sheet;
	_UpdateFrame();
}

void SimpleSpriteSheetRenderer::Advance(float dt) {
	
	
	//Not useful for now... but just in case
	SimpleSpriteRenderer::Advance(dt);

}

void SimpleSpriteSheetRenderer::SetIndex(int pos){
	_pos = pos;
	_UpdateFrame();
}

void SimpleSpriteSheetRenderer::Render(float dt) {
	
	SimpleSpriteRenderer::Render(dt);


}

void SimpleSpriteSheetRenderer::_UpdateFrame() {
	//Pick cell to render from sprite source
	glm::vec4 frame = _spriteSheet->GetCoordsForIndex(_pos);
	SimpleTexture *t = static_cast<SimpleTexture*>(_spriteSheet);
	if(t!= nullptr)
		SetAsTextureRect(t, glm::vec2{ frame.x, frame.y }, glm::vec2{ frame.z, frame.w });
}

json SimpleSpriteSheetRenderer::Serialize() {

	json so = SimpleSpriteRenderer::Serialize();
	json ret{
		{ "frameIndex", _pos },
		{ "spriteSheet", _spriteSheet->GetPath() }	
	};

	so["SimpleSpriteSheetRenderer"] = ret;
	return so;

}
bool SimpleSpriteSheetRenderer::Deserialize(json &node) {

	SimpleSpriteRenderer::Deserialize(node);

	json& local = node["SimpleSpriteSheetRenderer"];

	SIMPLE_ASSERT(local.find("frameIndex") != local.end());
	_pos = local["frameIndex"];

	SIMPLE_ASSERT(local.find("spriteSheet") != local.end());
	std::string sprPath = local["spriteSheet"];
	_spriteSheet = SimpleEngine::Instance()->GetRenderer()->GetSpriteSheet(sprPath);
	SIMPLE_ASSERT(_spriteSheet != nullptr);

	return true;
}