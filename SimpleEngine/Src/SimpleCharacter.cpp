#include "stdafx.h"
#include "SimpleCharacter.h"

//FACTORY_REGISTER(SimpleObject, SimpleCharacter)

SimpleCharacter::SimpleCharacter()
{
	_animator = new SimpleAnimator();
}

SimpleCharacter::~SimpleCharacter()
{
	delete _animator;
}

void SimpleCharacter::AddAnimation(std::string stateName, SimpleAnimatedSpriteRenderer* animation)
{
	this->_animator->AddAnimation(stateName, animation);
}

void SimpleCharacter::RemoveAnimation(std::string stateName)
{
	this->_animator->RemoveAnimation(stateName);
}

void SimpleCharacter::Advance(float dt) {
	
	if(_controller != nullptr)
		_controller->Advance(dt);
}

void SimpleCharacter::Render(float dt)
{
	flag++;
	if (flag > 500)
	{
		this->_animator->SwitchState("walk_left");
	}
	if (flag > 1000)
	{
		this->_animator->SwitchState("walk_rigth");
		flag = 0;
	}
	
	auto currentAnimation = this->_animator->GetCurrentState();
	if (currentAnimation != nullptr) {
		currentAnimation->SetPosition(this->GetPosition());
		auto size = this->GetSize();
		currentAnimation->SetSize(size);
		float orientation = GetOrientation();
		currentAnimation->SetOrientation(orientation);
		currentAnimation->Render(dt);
		currentAnimation->Advance(dt);
	}
}