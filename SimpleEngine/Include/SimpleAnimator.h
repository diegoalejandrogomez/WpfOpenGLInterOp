#pragma once
#include <map>
#include "SimpleAnimatedSpriteRenderer.h"

class SimpleAnimator{
public:
		SimpleAnimator();
		~SimpleAnimator();
		void AddAnimation(std::string, SimpleAnimatedSpriteRenderer*);
		void RemoveAnimation(std::string);
		void SwitchState(std::string);
		inline SimpleAnimatedSpriteRenderer* GetCurrentState() { return this->_currentState; };
private:
	std::map<std::string, SimpleAnimatedSpriteRenderer*>* _animations; //State name - Animation
	SimpleAnimatedSpriteRenderer* _currentState;
};
