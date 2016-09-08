#include "stdafx.h"
#include "SimpleController.h"
#include "SimpleDispatcher.h"

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


}