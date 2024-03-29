#include "stdafx.h"
#include "SimpleCharacter.h"
#include "SimpleDispatcher.h"
#include "SimpleEngine.h"
#include "HeroCharacter.h"
#include "HeroController.h"
#include "EnemyCharacter.h"


HeroCharacter::HeroCharacter() : SimpleCharacter()
{
	_controller = new HeroController();
	_controller->Control(this);
}

HeroCharacter::~HeroCharacter()
{
}

void HeroCharacter::Initialize() // to "Hero class"
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
}


bool HeroCharacter::OnBeginCollision(SimpleContactInfo& contactInfo) {

	if (dynamic_cast<SimpleCharacter*>(contactInfo.other) != nullptr) {
		SimpleNetworkManager *network = SimpleEngine::Instance()->GetNetwork();
		network->SendDirectMessage(SimpleNetworkManager::OWNER, GetNetworkObject(), contactInfo.other->GetNetworkObject(), NetworkMessageEvent{ nullptr, "Touched you" });
	}

	return false;
}

bool HeroCharacter::OnEndCollision(SimpleContactInfo& contactInfo) {

	return false;

}