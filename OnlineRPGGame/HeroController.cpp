#include "stdafx.h"
#include "HeroController.h"
#include "Events.h"

HeroController::HeroController() :SimplePlayerController()
{

}

HeroController::~HeroController()
{

}

void HeroController::Advance(float dt) {
	//to hero controller!!!!!
	auto keyboard = SimpleEngine::Instance()->GetInput()->GetKeyboard();
	glm::vec3 position = _character->GetPosition();
	int speed = _character->GetSpeed();
	glm::vec2 vel = _character->GetVelocity();

	if (_character != nullptr)
	{
		if (keyboard->isKeyDown(OIS::KeyCode::KC_LSHIFT))
		{
			speed = speed * 2;
		}

		if (keyboard->isKeyDown(OIS::KeyCode::KC_UP))
		{
			_character->ChangeAnimationState("walk_up");
			vel.y += speed;
			//_character->SetVelocity({ 0.0f, (float)speed });
			//_character->SetPosition(glm::vec3(position.x, position.y + speed, position.z));
		}

		if (keyboard->isKeyDown(OIS::KeyCode::KC_DOWN)) {
			_character->ChangeAnimationState("walk_down");
			vel.y += -speed;
			//_character->SetVelocity({ 0.0f, -(float)speed });		
			//_character->SetPosition(glm::vec3(position.x, position.y - speed, position.z));
		}

		if (keyboard->isKeyDown(OIS::KeyCode::KC_LEFT))
		{
			_character->ChangeAnimationState("walk_left");
			vel.x += -speed;
			//_character->SetVelocity({ -(float)speed, 0.0f });
			//_character->SetPosition(glm::vec3(position.x - speed, position.y, position.z));
		}

		if (keyboard->isKeyDown(OIS::KeyCode::KC_RIGHT))
		{
			_character->ChangeAnimationState("walk_rigth");
			vel.x += speed;
			//_character->SetVelocity({ (float)speed, 0.0f });
			//_character->SetPosition(glm::vec3(position.x + speed, position.y, position.z));
		}

		if (keyboard->isKeyDown(OIS::KeyCode::KC_A)) {
			SimpleEngine::Instance()->GetNetwork()->SendEvent(SimpleNetworkManager::OWNER, _character->GetNetworkObject(), _character->GetNetworkObject(), NetworkMessageEvent{ this,"Test" });
		}
		if (keyboard->isKeyDown(OIS::KeyCode::KC_S)) {
			SimpleEngine::Instance()->GetNetwork()->SendEvent(SimpleNetworkManager::OTHERS, _character->GetNetworkObject(), _character->GetNetworkObject(), NetworkMessageEvent{ this,"Test" });
		}
		if (keyboard->isKeyDown(OIS::KeyCode::KC_D)) {
			SimpleEngine::Instance()->GetNetwork()->SendEvent(SimpleNetworkManager::OTHERS_BUT_OWNER, _character->GetNetworkObject(), _character->GetNetworkObject(), NetworkMessageEvent{ this,"Test" });
		}
		if (keyboard->isKeyDown(OIS::KeyCode::KC_F)) {
			SimpleEngine::Instance()->GetNetwork()->SendEvent(SimpleNetworkManager::ALL, _character->GetNetworkObject(), _character->GetNetworkObject(), NetworkMessageEvent{ this,"Test" });
		}
		_character->SetVelocity( glm::clamp(vel, {-speed, -speed}, { speed, speed }));

	}
}

void HeroController::Render(float dt)
{

}