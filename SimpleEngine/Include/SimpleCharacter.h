#pragma once
#include <vector>
#include "SimpleSpriteRenderer.h"
#include "SimpleObject.h"
#include "SimpleAnimator.h"
#include "SimpleSpriteAnimation.h"
#include "SimpleController.h"

class SIMPLE_API SimpleCharacter : public SimpleObject {
public:
		SimpleCharacter();
		~SimpleCharacter();
		
		void AddAnimation(std::string, SimpleAnimatedSpriteRenderer*);
		void RemoveAnimation(std::string);
		virtual void Render(float dt) override;
		virtual void Advance(float dt) override;
		virtual void Die();
private:
	SimpleAnimator* _animator;
	SimpleController *_controller = nullptr;
	int flag = 0;
};
