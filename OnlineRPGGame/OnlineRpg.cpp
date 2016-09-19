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
	
}

void OnlineRpg::Init()
{

	SimpleEngine::Instance()->GetRenderer()->SetClearColor({ 0,0,0,0 });
	SimpleEngine::Instance()->GetRenderer()->ShowDebugInfo();

	//Configure input system we are going to use
	SimpleEngine::Instance()->GetInput()->CreateKeyboard(true);
	SimpleEngine::Instance()->GetInput()->CreateMouse(true);


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

// Inherited via SimpleGameLogic
void OnlineRpg::Advance(float dt)  {


}
void OnlineRpg::Shutdown()  {

	delete _character;
	delete _layer;
	delete _layerBackground;
	SimpleEngine::Instance()->Shutdown();

}
bool OnlineRpg::IsRunning()  {
	return true;
}
json OnlineRpg::Serialize()  {
	
	return {};
}

bool OnlineRpg::Deserialize(const json &node)  {

	return true;
}