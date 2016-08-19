#pragma once
#include "SimpleSpriteSheet.h"
#include "SimpleSerializable.h"

class SimpleSpriteAnimation: public SimpleSerializable {

	

public:
	
	SimpleSpriteAnimation() {};
	~SimpleSpriteAnimation() {};
	
	void SetAnimationName(const std::string name) { _name = name; }
	void SetSpriteSheet(SimpleSpriteSheet* sheet);
	void SetSpriteSheet(const std::string  sheetName);
	void SetFrames(const std::vector<int> &frames) { _frames = frames; }
	void SetFrameTime(float frameTime) { _frameTime = frameTime; }

	inline const float GetFrameTime() { return _frameTime; };
	inline const int GetFrameCount() { return _frames.size(); };
	inline const int GetFrame(int n) { return _frames[n]; }
	inline SimpleSpriteSheet* GetSpriteSheet() { return _sheet; };
	std::string GetAnimationName() { return _name;}

	json Serialize() override;
	bool Deserialize(json &node) override;

private:

	std::string _name;
	SimpleSpriteSheet * _sheet;

	std::vector<int> _frames;
	float _frameTime;
	


};
