#pragma once
#include <vector>
#include "SimpleSpriteRenderer.h"
#include "SimpleObject.h"
#include "SimpleAnimator.h"
#include "SimpleSpriteAnimation.h"
#include "SimpleController.h"
#include "SimpleAnimatedEntity.h"
#include <string>
class SIMPLE_API SimpleCharacter : public SimpleAnimatedEntity {
public:
		SimpleCharacter();
		~SimpleCharacter();
		
		virtual void Render(float dt) override;
		virtual void Advance(float dt) override;
		virtual void Die();
		virtual void Initialize(); // = 0
		int GetSpeed();
		void SetSpeed(int);
private:
	SimpleController* _controller = nullptr;
protected:
	int speed = 0;
};
