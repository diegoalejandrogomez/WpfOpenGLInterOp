#include "stdafx.h"
#include "SimpleCharacter.h"
#include "SimpleDispatcher.h"
#include "SimpleEngine.h"

//FACTORY_REGISTER(SimpleObject, SimpleCharacter)

SimpleCharacter::SimpleCharacter() : SimpleAnimatedEntity()
{
	SetSize({ 1,1 });
	InitDynamicPhysics(1.0f, 0.0f, 0.0f, false);
	FixOrientation(true);
	_body->SetLinearDamping(15.0f);
	

}

SimpleCharacter::~SimpleCharacter()
{
}

void SimpleCharacter::Advance(float dt) {
	
	SimpleAnimatedEntity::Advance(dt);
	if(_controller != nullptr)
		_controller->Advance(dt);
}

void SimpleCharacter::Render(float dt)
{
	SimpleAnimatedEntity::Render(dt);
}

//If character dies send the event so the controller knows
//SimpleDispatcher::Instance()->Send<CharacterDiedEvent>(this);
//Should do this for all the events that the character can emmit
void SimpleCharacter::Die() {
	SimpleDispatcher::Instance()->Send<CharacterDiedEvent>(this, this);
}

int SimpleCharacter::GetSpeed()
{
	return this->speed;
}

void SimpleCharacter::SetSpeed(int speed)
{
	this->speed = speed;
}