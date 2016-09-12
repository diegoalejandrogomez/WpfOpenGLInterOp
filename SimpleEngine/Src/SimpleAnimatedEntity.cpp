#include "stdafx.h"
#include "SimpleAnimatedEntity.h"
#include "SimpleDispatcher.h"
#include "SimpleEngine.h"

//FACTORY_REGISTER(SimpleObject, SimpleAnimatedEntity)

SimpleAnimatedEntity::SimpleAnimatedEntity()
{
	_animator = new SimpleAnimator();
}

SimpleAnimatedEntity::~SimpleAnimatedEntity()
{
	delete _animator;
}

void SimpleAnimatedEntity::AddAnimation(std::string stateName, SimpleAnimatedSpriteRenderer* animation)
{
	this->_animator->AddAnimation(stateName, animation);
}

void SimpleAnimatedEntity::RemoveAnimation(std::string stateName)
{
	this->_animator->RemoveAnimation(stateName);
}

void SimpleAnimatedEntity::Advance(float dt) {
		
}

void SimpleAnimatedEntity::Render(float dt)
{
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

void SimpleAnimatedEntity::ChangeAnimationState(std::string newState)
{
	this->_animator->SwitchState(newState);
}
