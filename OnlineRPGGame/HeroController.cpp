#include "stdafx.h"
#include "HeroController.h"

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

	if (_character != nullptr)
	{
		if (keyboard->isKeyDown(OIS::KeyCode::KC_LSHIFT))
		{
			speed = speed * 2;
		}

		if (keyboard->isKeyDown(OIS::KeyCode::KC_UP))
		{
			_character->ChangeAnimationState("walk_up");
			_character->SetVelocity({ 0.0f, (float)speed });
			//_character->SetPosition(glm::vec3(position.x, position.y + speed, position.z));
		}

		if (keyboard->isKeyDown(OIS::KeyCode::KC_DOWN)) {
			_character->ChangeAnimationState("walk_down");
			_character->SetVelocity({ 0.0f, -(float)speed });
			//_character->SetPosition(glm::vec3(position.x, position.y - speed, position.z));
		}

		if (keyboard->isKeyDown(OIS::KeyCode::KC_LEFT))
		{
			_character->ChangeAnimationState("walk_left");
			_character->SetVelocity({ -(float)speed, 0.0f });
			//_character->SetPosition(glm::vec3(position.x - speed, position.y, position.z));
		}

		if (keyboard->isKeyDown(OIS::KeyCode::KC_RIGHT))
		{
			_character->ChangeAnimationState("walk_rigth");
			_character->SetVelocity({ (float)speed, 0.0f });
			//_character->SetPosition(glm::vec3(position.x + speed, position.y, position.z));
		}

	}
}

void HeroController::Render(float dt)
{

}