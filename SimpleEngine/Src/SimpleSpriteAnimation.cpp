#include "stdafx.h"
#include "SimpleSpriteAnimation.h"
#include "SimpleEngine.h"
#include "SimpleRenderer.h"


void SimpleSpriteAnimation::SetSpriteSheet(const std::string sheetName) {
	_sheet = SimpleEngine::Instance()->GetResourceManager()->GetSpriteSheet(sheetName);
	SIMPLE_ASSERT(_sheet != nullptr);
}

void SimpleSpriteAnimation::SetSpriteSheet(SimpleSpriteSheet* sheet) {
	_sheet = sheet;
}


json SimpleSpriteAnimation::Serialize() {

	json frames = _frames;
	
	json ret{
		{ "name", _name },
		{ "frames", frames },
		{ "spriteSheet", _sheet->GetPath() },
		{ "frameTime", _frameTime }
	};

	return ret;

}

bool SimpleSpriteAnimation::Deserialize(const json &node, std::string dir)
{
	if (node.find("name") == node.end()) {
		SIMPLE_LOG("Couldn't deserialize animation");
		return false;
	}
	_name = node["name"].get<std::string>();

	if (node.find("frames") == node.end()) {
		SIMPLE_LOG("Couldn't deserialize animation");
		return false;
	}

	_frames.clear();
	for (auto f : node["frames"]) {
		_frames.push_back(f);
	}

	if (node.find("spriteSheet") == node.end()) {
		SIMPLE_LOG("Couldn't deserialize animation");
		return false;
	}

	std::string spriteSheet = node["spriteSheet"].get<std::string>();
	if (dir != "")
	{
		spriteSheet = dir + "/" + spriteSheet;
	}

	_sheet = SimpleEngine::Instance()->GetResourceManager()->GetSpriteSheet(spriteSheet);
	if (_sheet == nullptr) {
		SIMPLE_LOG("Couldn't find spritesheet");
		return false;
	}

	if (node.find("frameTime") == node.end()) {
		SIMPLE_LOG("Couldn't deserialize animation");
		return false;
	}
	_frameTime = node["frameTime"];

	return true;
}

bool SimpleSpriteAnimation::Deserialize(const json &node) {

	return this->Deserialize(node, "");
}