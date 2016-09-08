#include "stdafx.h"
#include "SimplePlayerController.h"
#include "SimpleDispatcher.h"

void SimplePlayerController::Advance(float dt) {


}
void SimplePlayerController::Render(float dt) {

}

//Callbacks
void SimplePlayerController::OnCharacterEvent(const SimpleEvent& event) {
	if (event.type() == CharacterDiedEvent::descriptor) {
		SIMPLE_LOG("SimplePlayerController - Character Died");
	}
}
