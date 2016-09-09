#include "stdafx.h"
#include "SimpleCharacter.h"
#include "SimpleDispatcher.h"
#include "SimpleEngine.h"

//FACTORY_REGISTER(SimpleObject, SimpleCharacter)

SimpleCharacter::SimpleCharacter()
{
	_animator = new SimpleAnimator();
	_controller = new SimpleController();
	_controller->Control(this);
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

//If character dies send the event so the controller knows
//SimpleDispatcher::Instance()->Send<CharacterDiedEvent>(this);
//Should do this for all the events that the character can emmit
void SimpleCharacter::Die() {
	SimpleDispatcher::Instance()->Send<CharacterDiedEvent>(this, this);
}

void SimpleCharacter::Initialize() // to "Hero class"
{
	auto animation = SimpleEngine::Instance()->GetResourceManager()->GetSpriteAnimation("walk_rigth");
	SimpleAnimatedSpriteRenderer* animatedSpriteRenderer = new SimpleAnimatedSpriteRenderer();
	animatedSpriteRenderer->SetAnimation(animation);
	this->AddAnimation("walk_rigth", animatedSpriteRenderer);
	auto animation2 = SimpleEngine::Instance()->GetResourceManager()->GetSpriteAnimation("walk_left");
	SimpleAnimatedSpriteRenderer* animatedSpriteRenderer2 = new SimpleAnimatedSpriteRenderer();
	animatedSpriteRenderer2->SetAnimation(animation2);
	this->AddAnimation("walk_left", animatedSpriteRenderer2);
	auto animation3 = SimpleEngine::Instance()->GetResourceManager()->GetSpriteAnimation("walk_up");
	SimpleAnimatedSpriteRenderer* animatedSpriteRenderer3 = new SimpleAnimatedSpriteRenderer();
	animatedSpriteRenderer3->SetAnimation(animation3);
	this->AddAnimation("walk_up", animatedSpriteRenderer3);
	auto animation4 = SimpleEngine::Instance()->GetResourceManager()->GetSpriteAnimation("walk_down");
	SimpleAnimatedSpriteRenderer* animatedSpriteRenderer4 = new SimpleAnimatedSpriteRenderer();
	animatedSpriteRenderer4->SetAnimation(animation4);
	this->AddAnimation("walk_down", animatedSpriteRenderer4);
	this->SetSize(glm::vec2(60, 60));
}

void SimpleCharacter::ChangeAnimationState(std::string newState)
{
	this->_animator->SwitchState(newState);
}

int SimpleCharacter::GetSpeed()
{
	return this->speed;
}

void SimpleCharacter::SetSpeed(int speed)
{
	this->speed = speed;
}