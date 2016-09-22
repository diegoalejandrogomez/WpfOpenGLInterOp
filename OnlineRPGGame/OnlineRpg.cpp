#include "stdafx.h"
#include "OnlineRpg.h"
#include "EnemyCharacter.h"
#include "SimpleNetworkManager.h"

OnlineRpg::OnlineRpg()
{
	SimpleEngine::Instance()->GetResourceManager()->ImportResources("./resources/ash.pack", "ash");
	SimpleEngine::Instance()->GetResourceManager()->ImportResources("./resources/trees.pack", "tree");
	SimpleEngine::Instance()->CreateScene();
	
	_layer = new SimpleLayer();
	_layer->SetName("GameLayer");
	_layerBackground = new SimpleLayer();
	_layerBackground->SetName("BackgroundLayer");
	_layer->SetZ(0);
	_layerBackground->SetZ(-1);
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

	SimpleEngine::Instance()->GetScene()->AddLayer(_layer);
	SimpleEngine::Instance()->GetScene()->AddLayer(_layerBackground);

	if (_isServer) {
		SimpleEngine::Instance()->GetNetwork()->InitServer(0U);
		
		for (int i = 0; i < 1; i++)
		{
			EnemyCharacter* enemy = new EnemyCharacter();
			enemy->SetSpeed(rand() % 100 + 100);
			enemy->Initialize();
			SimpleEngine::Instance()->GetScene()->AddEntity(enemy, _layerBackground);
			enemy->InitNetwork();
			enemy->Replicate();		
		}

		for (int i = 0; i < 0; i++)
		{
			SimpleFixedObject* tree = new SimpleFixedObject();
			tree->Initialize();
			glm::vec3 position = tree->GetPosition();
			tree->SetPosition(glm::vec3(position.x, position.y, 0.0f));
			SimpleEngine::Instance()->GetScene()->AddEntity(tree, _layerBackground);
			tree->InitNetwork();
			tree->Replicate();
		}

	}
	else {
		SimpleEngine::Instance()->GetNetwork()->InitClient(_ip, 0U);

		_character = new HeroCharacter();
		_character->Initialize();
		_character->SetSpeed(200);
				
		SimpleEngine::Instance()->GetScene()->AddEntity(_character, _layer);
		_character->InitNetwork();
		_character->Replicate();
	}
	
	InitNetwork();
}

// Inherited via SimpleGameLogic
void OnlineRpg::Advance(float dt)  {
	using namespace std::chrono;

	if (SimpleEngine::Instance()->GetNetwork()->IsServer()) {
		static high_resolution_clock::time_point prev = high_resolution_clock::now();
		high_resolution_clock::time_point current = high_resolution_clock::now();
		std::chrono::duration<float> _elapsed = current - prev;
		if (_elapsed.count() > 10.0f) {
			prev = current;
			SimpleEngine::Instance()->GetNetwork()->SendEvent(SimpleNetworkManager::OTHERS_BUT_OWNER, nullptr, nullptr, NetworkMessageEvent{ this,"The server is watching..." });
		}
	}

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

