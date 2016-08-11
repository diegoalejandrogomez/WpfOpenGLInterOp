#pragma once
#include "stdafx.h"
#include "SimpleSpriteSheetRenderer.h"
#include "SimpleSpriteAnimation.H"

class SimpleAnimatedSpriteRenderer : public SimpleSpriteSheetRenderer {
public:

	SimpleAnimatedSpriteRenderer();
	~SimpleAnimatedSpriteRenderer();
	void Advance(float dt);
	void Render(float dt);

	void SetAnimation(SimpleSpriteAnimation* anim);
	
	void Play();
	void PlayOnce();
	void Stop();
	void Pause();
	
protected:
	SimpleSpriteAnimation* _anim;
	int _currentFrame;
	float _elapsedTime;
	bool _playing;
	bool _loop;

};

