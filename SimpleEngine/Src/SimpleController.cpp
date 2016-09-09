#include "stdafx.h"
#include "SimpleController.h"
#include "SimpleDispatcher.h"
#include "SimpleEngine.h"
#include "SimpleCharacter.h"
FACTORY_REGISTER(SimpleObject, SimpleController)



void SimpleController::Control(SimpleCharacter* character) {
	
	_character = character;
	_RegisterDefaultListeners();
	
}


void SimpleController::_RegisterDefaultListeners() {

	//Register to receive the default messages
	SimpleDispatcher::Instance()->AddObjectListener(_character,
		CharacterDiedEvent::descriptor,
		{ this,
		std::bind(&SimpleController::OnCharacterEvent,this, std::placeholders::_1) });

}
void SimpleController::_UnregisterDefaultListeners() {


	//Remove common event registration
	SimpleDispatcher::Instance()->RemoveObjectListener(_character, CharacterDiedEvent::descriptor, this);
}


void SimpleController::OnCharacterEvent(const SimpleEvent& event) {

	if (event.type() == CharacterDiedEvent::descriptor) {
		SIMPLE_LOG("SimpleController - Character Died");
	}
	
}
void SimpleController::Release(SimpleCharacter* character) {

	_UnregisterDefaultListeners();
	_character = nullptr;

}

void SimpleController::Render(float dt) {

}
void SimpleController::Advance(float dt) {
	//to hero controller!!!!!
	auto keyboard = SimpleEngine::Instance()->GetInput()->GetKeyboard();
	glm::vec3 position = _character->GetPosition();
	int speed = _character->GetSpeed();

	if (_character != nullptr)
	{
		if (keyboard->isKeyDown(OIS::KeyCode::KC_LSHIFT))
		{
			speed = speed * 2;
		}

		if (keyboard->isKeyDown(OIS::KeyCode::KC_UP))
		{
			_character->ChangeAnimationState("walk_up");
			_character->SetPosition(glm::vec3(position.x, position.y + speed, position.z));
		}
			
		if (keyboard->isKeyDown(OIS::KeyCode::KC_DOWN)) {
			_character->ChangeAnimationState("walk_down");
			_character->SetPosition(glm::vec3(position.x, position.y - speed, position.z));
		}
			
		if (keyboard->isKeyDown(OIS::KeyCode::KC_LEFT))
		{
			_character->ChangeAnimationState("walk_left");
			_character->SetPosition(glm::vec3(position.x - speed, position.y, position.z));
		}
			
		if (keyboard->isKeyDown(OIS::KeyCode::KC_RIGHT))
		{
			_character->ChangeAnimationState("walk_rigth");
			_character->SetPosition(glm::vec3(position.x + speed, position.y, position.z));
		}
			
	}
}