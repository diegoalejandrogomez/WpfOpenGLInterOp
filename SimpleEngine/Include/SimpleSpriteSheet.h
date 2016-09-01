#pragma once
#include "SimpleTexture.h"
#include "SimpleAABB.h"
#include <stdlib.h>
#include <vector>
#include "json.hpp"
#include "SimpleSerializable.h"
#include "SimpleConfiguration.h"

using json = nlohmann::json;

class SIMPLE_API SimpleSpriteSheet : public SimpleTexture, SimpleSerializable{

public:

	SimpleSpriteSheet();
	~SimpleSpriteSheet();

	void CreateUniformFrames(glm::ivec2 size, glm::ivec2 count);
	int AddSpriteFrame(glm::ivec2 position, glm::ivec2 size, bool inverted = true);
	int GetFrameIndex(glm::ivec2 position, glm::ivec2 size);
	void ClearFrames() { _frames.clear(); }
	glm::ivec4 GetCoordsForIndex(int idx);

	json Serialize() override;
	bool Deserialize(const json &node) override;
private:

	//XY contains origin, ZW contains size
	std::vector<glm::ivec4> _frames;

	glm::ivec2 _spriteCellSize;
	glm::ivec2 _spriteCellCount;

};
