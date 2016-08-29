#pragma once
#include "stdafx.h"
#include "SimpleSpriteSheetRenderer.h"
#include "SimpleSpriteAnimation.H"
#include "SimpleConfiguration.h"


class SIMPLE_API SimpleAnimatedSpriteRenderer : public SimpleSpriteSheetRenderer {
public:

	SimpleAnimatedSpriteRenderer();
	~SimpleAnimatedSpriteRenderer();
	void Advance(float dt);
	void Render(float dt);

	void SetAnimation(SimpleSpriteAnimation* anim);
	void SetAnimation(SimpleID animName);
	SimpleSpriteAnimation* GetAnimation() { return _anim; }
	
	void Play();
	void PlayOnce();
	void Stop();
	void Pause();

	virtual SimpleID GetType() { return "SimpleAnimatedSpriteRenderer"; }

	virtual json Serialize() override;
	virtual bool Deserialize(json &node) override;
	
protected:
	SimpleSpriteAnimation* _anim;
	int _currentFrame;
	float _elapsedTime;
	bool _playing;
	bool _loop;
};

