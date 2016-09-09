#pragma once
#include "SimpleSpriteSheet.h"
#include "SimpleSerializable.h"
#include "SimpleConfiguration.h"

class SIMPLE_API SimpleSpriteAnimation: public SimpleSerializable {

	

public:
	
	SimpleSpriteAnimation() {};
	~SimpleSpriteAnimation() {};
	
	void SetAnimationName(const std::string name) { _name = name; }
	void SetSpriteSheet(SimpleSpriteSheet* sheet);
	void SetSpriteSheet(const std::string  sheetName);
	void SetFrames(const std::vector<int> &frames) { _frames = frames; }
	void AddFrame(int idx) { _frames.push_back(idx);}
	void ClearFrames() { _frames.clear(); };
	void SetFrameTime(float frameTime) { _frameTime = frameTime; }

	inline const float GetFrameTime() const { return _frameTime; };
	inline const int GetFrameCount() const { return _frames.size(); };
	inline const int GetFrame(int n) const { return _frames[n]; }
	inline SimpleSpriteSheet* GetSpriteSheet() { return _sheet; };
	std::string GetAnimationName() const { return _name;}

	json Serialize() override;
	bool Deserialize(const json &node) override;
	bool Deserialize(const json &node, std::string dir) override;
private:

	std::string _name;
	SimpleSpriteSheet * _sheet;

	std::vector<int> _frames;
	float _frameTime;
	


};
