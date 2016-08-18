#include "stdafx.h"
#include "SimpleSpriteSheet.h"
#include "SimpleAABB.h"

SimpleSpriteSheet::SimpleSpriteSheet() {

}
SimpleSpriteSheet::~SimpleSpriteSheet() {

}

int SimpleSpriteSheet::AddSpriteFrame(glm::ivec2 position, glm::ivec2 size) {
	
	_frames.emplace_back(position.x, GetHeight() - size.y - position.y, size.x, size.y);
	return _frames.size()-1;
}


int SimpleSpriteSheet::GetFrameIndex(glm::ivec2 position, glm::ivec2 size) {

	for (unsigned int i = 0; i < _frames.size(); ++i)
		if (_frames[i] == glm::ivec4{ position.x, position.y, size.x, size.y })
			return i;
	return -1;	
}

void SimpleSpriteSheet::CreateUniformFrames(glm::ivec2 size, glm::ivec2 count) {

	for (int i = 0;i < count.y; ++i) 
		for (int j = 0; j < count.x; ++j)
			_frames.emplace_back(j*size.x, GetHeight() - (i+1)*size.y, size.x, size.y);
	
	_spriteCellSize = size;
	_spriteCellCount = count;
	
}


glm::ivec4 SimpleSpriteSheet::GetCoordsForIndex(int idx) {

	SIMPLE_ASSERT(idx < _spriteCellCount.x * _spriteCellCount.y);

	//Return the pixel coordinates for the current sheet
	return _frames[idx];
}

json SimpleSpriteSheet::Serialize() {
	json frames = json::array();
	for (glm::ivec4 &frame : _frames) {
		json f{ {"from", {frame.x, frame.y}},
				{"to", {frame.z, frame.w }} };
		frames.push_back(f);
	}
	json ret{
		{"path", GetPath()},
		{"frames", frames},
		{"cellSize", {_spriteCellSize.x, _spriteCellSize.y} },
		{"cellCount", {_spriteCellCount.x, _spriteCellCount.y}}
	};

	return ret;

}
bool SimpleSpriteSheet::Deserialize(json &node) {
	
	if (node.find("frames") == node.end()) {
		SIMPLE_LOG("Couldn't deserialize frames");
		return false;	
	}

	json &frames = node["frames"];
	for (auto frame : frames) {
		_frames.emplace_back(	frame["from"][0],
								frame["from"][1],
								frame["to"][0],
								frame["to"][1]);
	}

	if (node.find("path") == node.end()) {
		SIMPLE_LOG("Couldn't deserialize path");
		return false;
	}
	std::string path = node["path"];
	LoadTexture(path.c_str());
	
	if (node.find("cellSize") == node.end()) {
		SIMPLE_LOG("Couldn't deserialize cellSize");
		return false;
	}
	_spriteCellSize.x = node["cellSize"][0];
	_spriteCellSize.y = node["cellSize"][1];

	if (node.find("cellCount") == node.end()) {
		SIMPLE_LOG("Couldn't deserialize cellCount");
		return false;
	}
	_spriteCellCount.x = node["cellCount"][0];
	_spriteCellCount.y = node["cellCount"][1];

	return true;
}