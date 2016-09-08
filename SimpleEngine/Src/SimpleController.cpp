#include "stdafx.h"
#include "SimpleController.h"
#include "SimpleDispatcher.h"

FACTORY_REGISTER(SimpleObject, SimpleController)



void SimpleController::Control(SimpleCharacter* character) {
	
	//Register to receive the default messages
	SimpleDispatcher::Instance()->AddObjectListener(character,
													CharacterDiedEvent::descriptor, 
													{ this, 
													std::bind(&SimpleController::OnCharacterEvent,this, std::placeholders::_1) } );
	
}

void SimpleController::OnCharacterEvent(const SimpleEvent& event) {

	if (event.type() == CharacterDiedEvent::descriptor) {
		SIMPLE_LOG("Character Died");
	}
	
}
void SimpleController::Release(SimpleCharacter* character) {

	//Remove common event registration
	SimpleDispatcher::Instance()->RemoveObjectListener(character, CharacterDiedEvent::descriptor, this);

}

void SimpleController::Render(float dt) {

}
void SimpleController::Advance(float dt) {


}