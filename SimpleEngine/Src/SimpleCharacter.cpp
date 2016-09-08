#include "stdafx.h"
#include "SimpleCharacter.h"
SimpleCharacter::SimpleCharacter()
{
	_animator = new SimpleAnimator();
}

SimpleCharacter::~SimpleCharacter()
{
	delete _mainSprite;
	delete _animator;
}


void SimpleCharacter::SetMainSprite(SimpleAnimatedSpriteRenderer* mainSprite)
{
	this->_mainSprite = mainSprite;
}

SimpleSpriteRenderer* SimpleCharacter::GetMainSprite()
{
	return _mainSprite;
}

void SimpleCharacter::AddAnimation(std::string stateName, SimpleAnimatedSpriteRenderer* animation)
{
	this->_animator->AddAnimation(stateName, animation);
}

void SimpleCharacter::RemoveAnimation(std::string stateName)
{
	this->_animator->RemoveAnimation(stateName);
}

void SimpleCharacter::Render(float dt)
{
	//controller.Update

	auto currentAnimation = this->_animator->GetCurrentState();
	if (currentAnimation != nullptr) {
		currentAnimation->SetPosition(this->GetPosition());
		auto size = this->GetSize();
		currentAnimation->SetSize(size);
		currentAnimation->SetAnchor(this->GetAnchor());
		float orientation = GetOrientation();
		currentAnimation->SetOrientation(orientation);
		currentAnimation->Play();
	}
}