#pragma once
#include <vector>
#include "SimpleSpriteRenderer.h"
#include "SimpleObject.h"
#include "SimpleAnimator.h"
#include "SimpleSpriteAnimation.h"
#include "SimpleController.h"

class SimpleCharacter : public SimpleObject {
public:
		SimpleCharacter();
		~SimpleCharacter();
		
		void SetMainSprite(SimpleAnimatedSpriteRenderer* mainSprite);
		SimpleSpriteRenderer* GetMainSprite();
		void AddAnimation(std::string, SimpleAnimatedSpriteRenderer*);
		void RemoveAnimation(std::string);
		virtual void Render(float dt) override;
		virtual void Advance(float dt) override;
private:
	SimpleAnimatedSpriteRenderer* _mainSprite;
	SimpleAnimator* _animator;
	SimpleController *_controller;
};
