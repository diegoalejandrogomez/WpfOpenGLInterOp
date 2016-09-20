#include "stdafx.h"
#include "SimpleAnimator.h"
SimpleAnimator::SimpleAnimator()
{
	_animations = new std::map<std::string, SimpleAnimatedSpriteRenderer*>();
}

SimpleAnimator::~SimpleAnimator()
{
	delete _animations;
}

void SimpleAnimator::AddAnimation(std::string stateName, SimpleAnimatedSpriteRenderer* animation){
	auto element = std::pair<std::string, SimpleAnimatedSpriteRenderer*>(stateName, animation);
	if (_animations->count(stateName)  == 0)
	{
		_animations->insert(element);
	}
	else
	{
		SIMPLE_LOG("Status key already exists");
	}

	if (_animations->size() == 1)
	{
		//if it is the first one, it should be the current state
		this->SwitchState(stateName);
	}
	
}

void SimpleAnimator::RemoveAnimation(std::string stateName)
{
	_animations->erase(stateName);
	if (_animations->size() == 0)
	{
		this->_currentState = nullptr;
	}
}

void SimpleAnimator::SwitchState(std::string newState) 
{
	auto state = _animations->at(newState);
	if (state != nullptr)
	{
		//SIMPLE_LOG("Cannot swith to state, because it doesn't exist");
	}

	this->_currentState = state;
	this->_currentState->PlayOnce();
}
