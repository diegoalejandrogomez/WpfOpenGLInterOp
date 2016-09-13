#include "stdafx.h"
#include "OnlineRpg.h"
#include "EnemyCharacter.h"

OnlineRpg::OnlineRpg()
{
	SimpleEngine::Instance()->GetResourceManager()->ImportResources("./resources/ash.pack", "ash");
	SimpleEngine::Instance()->GetResourceManager()->ImportResources("./resources/trees.pack", "tree");
	SimpleEngine::Instance()->CreateScene();
	_character = new HeroCharacter();
	_layer = new SimpleLayer();
	_layerBackground = new SimpleLayer();
}

OnlineRpg::~OnlineRpg()
{
	delete _character;
	delete _layer;
	delete _layerBackground;
	SimpleEngine::Instance()->Shutdown();
}

void OnlineRpg::Initialize()
{
	_character->Initialize();
	_character->SetSpeed(200);
	_layer->SetZ(0);
	_layerBackground->SetZ(-1);

	SimpleEngine::Instance()->GetScene()->AddLayer(_layer);
	SimpleEngine::Instance()->GetScene()->AddLayer(_layerBackground);

	SimpleEngine::Instance()->GetScene()->AddEntity(_character, _layer);
	
	int z = 0;
	for (int i = 0; i < 50; i++)
	{
		SimpleFixedObject* tree = new SimpleFixedObject();
		tree->Initialize();
		glm::vec3 position = tree->GetPosition();
		tree->SetPosition(glm::vec3(position.x, position.y, z));
		z--;
		//SimpleEngine::Instance()->GetScene()->AddEntity(tree, _layerBackground);
	}

	for (int i = 0; i < 5; i++)
	{
		EnemyCharacter* enemy = new EnemyCharacter();
		enemy->SetSpeed(rand() % 100 + 100);
		enemy->Initialize();
		SimpleEngine::Instance()->GetScene()->AddEntity(enemy, _layerBackground);
	}

}