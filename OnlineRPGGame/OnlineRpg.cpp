#include "stdafx.h"
#include "OnlineRpg.h"
#include "EnemyCharacter.h"
#include "SimpleNetworkManager.h"

OnlineRpg::OnlineRpg()
{
	SimpleEngine::Instance()->GetResourceManager()->ImportResources("./resources/ash.pack", "ash");
	SimpleEngine::Instance()->GetResourceManager()->ImportResources("./resources/trees.pack", "tree");
	SimpleEngine::Instance()->CreateScene();
	_character = new HeroCharacter();
	_layer = new SimpleLayer();
	_layer->SetName("GameLayer");
	_layerBackground = new SimpleLayer();
	_layerBackground->SetName("BackgroundLayer");
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


	/*_character->Initialize();
	_character->SetSpeed(200);
	_layer->SetZ(0);
	_layerBackground->SetZ(-1);*/

	SimpleEngine::Instance()->GetScene()->AddLayer(_layer);
	SimpleEngine::Instance()->GetScene()->AddLayer(_layerBackground);

	//SimpleEngine::Instance()->GetScene()->AddEntity(_character, _layer);
	
	

	/*for (int i = 0; i < 5; i++)
	{
		EnemyCharacter* enemy = new EnemyCharacter();
		enemy->SetSpeed(rand() % 100 + 100);
		enemy->Initialize();
		SimpleEngine::Instance()->GetScene()->AddEntity(enemy, _layerBackground);
	}*/

	if (_isServer) {
		SimpleEngine::Instance()->GetNetwork()->InitServer(0U);
		int z = 0;
		for (int i = 0; i < 1; i++)
		{
			SimpleFixedObject* tree = new SimpleFixedObject();
			tree->Initialize();
			glm::vec3 position = tree->GetPosition();
			tree->SetPosition(glm::vec3(position.x, position.y, z));
			z--;
			SimpleEngine::Instance()->GetScene()->AddEntity(tree, _layerBackground);
			tree->InitNetwork();
			tree->Replicate();
		}

	}
	else {
		SimpleEngine::Instance()->GetNetwork()->InitClient("127.0.0.1", 0U);
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

