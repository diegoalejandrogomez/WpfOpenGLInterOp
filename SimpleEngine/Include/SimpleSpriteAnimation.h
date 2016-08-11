#pragma once
#include "SimpleSpriteSheet.h"

class SimpleSpriteAnimation {

	

public:
	typedef std::pair<unsigned char, unsigned char> AnimationIndex;

	SimpleSpriteAnimation() {};
	~SimpleSpriteAnimation() {};
	
	void SetAnimationName(const std::string name) { _name = name; }
	void SetSpriteSheet(SimpleSpriteSheet* sheet);
	void SetSpriteSheet(const std::string  sheetName);
	void SetFrames(const std::vector<AnimationIndex> &frames) { _frames = frames; }
	void SetFrameTime(float frameTime) { _frameTime = frameTime; }

	inline const float GetFrameTime() { return _frameTime; };
	inline const int GetFrameCount() { return _frames.size(); };
	inline const AnimationIndex& GetFrame(int n) { return _frames[n]; }
	inline SimpleSpriteSheet* GetSpriteSheet() { return _sheet; };
	std::string GetAnimationName() { return _name;}

private:

	std::string _name;
	SimpleSpriteSheet * _sheet;
	//XY frame pairs - Could be linear.. but for now its easier to read this way
	std::vector<AnimationIndex> _frames;
	float _frameTime;
	


};
