#include "stdafx.h"
#include "EnemyController.h"

EnemyController::EnemyController() :SimplePlayerController()
{

}

EnemyController::~EnemyController()
{

}

void EnemyController::Advance(float dt) {
	auto keyboard = SimpleEngine::Instance()->GetInput()->GetKeyboard();
	glm::vec3 position = _character->GetPosition();
	int speed = _character->GetSpeed();

	if (_character != nullptr)
	{
		if (index < 150)
		{
			_character->ChangeAnimationState("walk_rigth");
			//_character->SetPosition(glm::vec3(position.x + speed, position.y, position.z));
			_character->SetVelocity({ (float)speed , 0.0f});
		}
		else if (index >= 150 && index < 300)
		{
			_character->ChangeAnimationState("walk_up");
			//_character->SetPosition(glm::vec3(position.x, position.y + speed, position.z));
			_character->SetVelocity({ 0.0f, (float)speed });
		}
		else if (index >= 300 && index < 450)
		{
			_character->ChangeAnimationState("walk_left");
			//_character->SetPosition(glm::vec3(position.x - speed , position.y, position.z));
			_character->SetVelocity({ -(float)speed , 0.0f });
		}
		else if (index >= 450 && index < 600)
		{
			_character->ChangeAnimationState("walk_down");
			//_character->SetPosition(glm::vec3(position.x, position.y - speed, position.z));
			_character->SetVelocity({ 0.0f, -(float)speed });
		}
		else
		{
			index = 0;
		}

		index++;
	}
}

void EnemyController::Render(float dt)
{

}