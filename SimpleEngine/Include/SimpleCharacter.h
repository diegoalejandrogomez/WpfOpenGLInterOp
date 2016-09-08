#pragma once
#include <vector>
#include "SimpleSpriteRenderer.h"
#include "SimpleObject.h"
#include "SimpleAnimator.h"
#include "SimpleSpriteAnimation.h"

class SimpleCharacter : SimpleObject {
public:
		SimpleCharacter();
		~SimpleCharacter();
		
		void SetMainSprite(SimpleAnimatedSpriteRenderer* mainSprite);
		SimpleSpriteRenderer* GetMainSprite();
		void AddAnimation(std::string, SimpleAnimatedSpriteRenderer*);
		void RemoveAnimation(std::string);
		virtual void Render(float dt) override;
private:
	SimpleAnimatedSpriteRenderer* _mainSprite;
	SimpleAnimator* _animator;
};
