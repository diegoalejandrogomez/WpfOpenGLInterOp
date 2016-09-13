#include "stdafx.h"
#include "SimpleCharacter.h"
#include "SimpleDispatcher.h"
#include "SimpleEngine.h"
#include "EnemyCharacter.h"
#include "EnemyController.h"

EnemyCharacter::EnemyCharacter() : SimpleCharacter()
{
	_controller = new EnemyController();
	_controller->Control(this);
}

EnemyCharacter::~EnemyCharacter()
{
}

void EnemyCharacter::Initialize() // to "Enemy class"
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

	this->SetPosition(glm::vec3(rand()% 350 * (rand()% 2 == 0? -1 : 1), rand() % 350 * (rand() % 2 == 0 ? -1 : 1), 0));
}

