#include "stdafx.h"
#include "SimplePlayerController.h"
#include "SimpleDispatcher.h"

//FACTORY_REGISTER(SimpleObject, SimplePlayerController)

//Callbacks
void SimplePlayerController::OnCharacterEvent(const SimpleEvent& event) {
	if (event.type() == CharacterDiedEvent::descriptor) {
		SIMPLE_LOG("SimplePlayerController - Character Died");
	}
}
