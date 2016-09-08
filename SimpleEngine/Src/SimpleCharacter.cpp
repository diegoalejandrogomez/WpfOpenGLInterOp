#include "stdafx.h"
#include "SimpleCharacter.h"
#include "SimpleDispatcher.h"

FACTORY_REGISTER(SimpleObject, SimpleCharacter)

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

void SimpleCharacter::Advance(float dt) {
	
	if(_controller != nullptr)
		_controller->Advance(dt);


	//If character dies send the event so the controller knows
	//SimpleDispatcher::Instance()->Send<CharacterDiedEvent>(this);
	//Should do this for all the events that the character can emmit
}

void SimpleCharacter::Die() {
	SimpleDispatcher::Instance()->Send<CharacterDiedEvent>(this, this);
	//SimpleDispatcher::Instance()->SendImmediate<CharacterDiedEvent>(this, this);
}

void SimpleCharacter::Render(float dt)
{


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