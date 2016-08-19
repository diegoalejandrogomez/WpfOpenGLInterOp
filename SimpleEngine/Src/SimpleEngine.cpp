#include "stdafx.h"
#include "SimpleEngine.h"
#include "DebugRenderPass.h"
#include "SimpleObjectsRenderPass.h"
#include "SimpleDispatcher.h"
#include "DebugGameLogic.h"
#include <filesystem>
#include <fstream>
//C++ 14/17 ... but why not XD
using namespace std::tr2::sys;
using namespace std::chrono;

void SimpleEngine::InitRenderer(HWND hWnd, uint32_t width, uint32_t height) {
	
	_renderer = new SimpleRenderer();
	_renderer->InitializeOpenGL(hWnd, width, height);
	
	
}


void SimpleEngine::InitInput(HWND hWnd, bool exclusive) {

	//Create a simple input instance once the renderer is configured
	_input = new SimpleInput();
	_input->Initialize(hWnd, exclusive);

}

void SimpleEngine::SetGameLogic(SimpleGameLogic* _newGameLogic) {

	_nextGameLogic = _newGameLogic;
}

void SimpleEngine::CreateScene() {
	if (_scene != nullptr) 
		delete _scene;
	_scene = new SimpleScene();
}
void SimpleEngine::_SwitchGameLogic() {

	if (_gameLogic != nullptr) {
		_gameLogic->Shutdown();
		delete _gameLogic;
	}
	_gameLogic = _nextGameLogic;
	if (_gameLogic != nullptr) { //Could be switching to nullptr
		_gameLogic->Init();
		_nextGameLogic = nullptr;
	}

}

void SimpleEngine::Render(float dt) {
	

	SIMPLE_ASSERT(_renderer != nullptr);

	//Internal fps measuring
	static high_resolution_clock::time_point prev = high_resolution_clock::now();
	high_resolution_clock::time_point current = high_resolution_clock::now();
	_renderTime = duration_cast<nanoseconds>(current - prev);
	prev = current;
	
	if(_scene != nullptr)
		_renderer->Render(dt, _scene);
}

void SimpleEngine::Advance(float dt) {
	
	//Internal fps measuring
	static high_resolution_clock::time_point prev = high_resolution_clock::now();
	high_resolution_clock::time_point current = high_resolution_clock::now();
	_logicTime = duration_cast<nanoseconds>(current - prev);
	prev = current;

	////Check if we must switch the game mode
	if (_nextGameLogic != nullptr)
		_SwitchGameLogic();

	//Capture buffered input
	_input->Capture();

	if (_gameLogic != nullptr && _gameLogic->IsRunning()) {
		_gameLogic->Advance(dt);
		if (_scene != nullptr)
			_scene->Advance(dt);
	}

	//Flush pending events
	SimpleDispatcher::Instance()->Flush();

	//SIMPLE_LOG("FPS: %.2f", GetRenderFPS());
}

#define DEBUG_CONTENT
void SimpleEngine::Initialize() {

	SIMPLE_ASSERT(_renderer != nullptr);
	SIMPLE_ASSERT(_input != nullptr);
	
	//Init render passes
	_renderer->Initialize();
	
	_resBaseDir = "./resources/";

	//Loads a default scene
	CreateScene();
	_scene->GetCamera()->SetViewportSize((float)_renderer->GetWidth(), (float)_renderer->GetHeight());

#ifdef DEBUG_CONTENT
	SetGameLogic(new DebugGameLogic());
#endif

}
void SimpleEngine::Shutdown() {

	//Destroy GameLogic
	if (_gameLogic != nullptr) {
		_gameLogic->Shutdown();
		delete _gameLogic;
		_gameLogic = nullptr;
	}

	if (_nextGameLogic != nullptr) {
		//Was never initialized
		delete _nextGameLogic;
		_nextGameLogic = nullptr;
	}
	
	//Destroy scene
	if (_scene != nullptr) {
		delete _scene;
		_scene = nullptr;
	}

	//Destroy resources
	_renderer->Shutdown();

}

void SimpleEngine::SerializeResources() {

	//Create the dir for the resources
	
	create_directory(_resBaseDir);

	//Serialize graphical resources
	_renderer->SerializeResources(_resBaseDir);

}
void SimpleEngine::DeserializeResources() {
	_renderer->DeserializeResources(_resBaseDir);
}

void SimpleEngine::SetResourcesBaseDir(std::string baseDir) {
	_resBaseDir = baseDir;
}

bool SimpleEngine::SerializeGameLogic(std::string path) {
	json logic = _gameLogic->Serialize();
	std::ofstream file(SimpleEngine::Instance()->GetResourcesBaseDir() + path);
	if (file.is_open()) {
		file << std::setw(4) << logic;
		file.close();
		return true;
	}
	return false;

}
bool SimpleEngine::DeserializeGameLogic(std::string path) {
	
	json logic;

	std::ifstream file(SimpleEngine::Instance()->GetResourcesBaseDir() + path);
	if (file.is_open())
	{
		file >> logic;
		file.close();
		return _gameLogic->Deserialize(logic);
	}
	return false;
	
}

std::string SimpleEngine::GetGameLogicState() {
	json logic = _gameLogic->Serialize();
	return logic.dump(4);
}
void SimpleEngine::SetGameLogicState(std::string state) {
	json logic = json::parse(state);
	_gameLogic->Deserialize(logic);
}

bool SimpleEngine::SerializeScene(std::string path) {

	json scene = _scene->Serialize();
	std::ofstream file(SimpleEngine::Instance()->GetResourcesBaseDir() + path);
	if (file.is_open()) {
		file << std::setw(4) << scene;
		file.close();
		return true;
	}
	return false;

}
bool SimpleEngine::DeserializeScene(std::string path) {

	json scene;
	CreateScene();
	_scene->RemoveLayer(_scene->GetLayer(0));

	std::ifstream file(SimpleEngine::Instance()->GetResourcesBaseDir() + path);
	if (file.is_open())
	{
		file >> scene;
		file.close();
		return _scene->Deserialize(scene);
	}
	return false;

}

std::string SimpleEngine::GetSceneState() {
	json scene = _scene->Serialize();
	return scene.dump(4);
}
bool SimpleEngine::SetSceneState(std::string state) {
	json scene = json::parse(state);
	_scene->Deserialize(scene);
	return true;
}

bool SimpleEngine::SerializeGameState(std::string path) {

	json logic = _gameLogic->Serialize();
	json scene = _scene->Serialize();
	json gameState = {
		{"gameLogic", logic},
		{"scene", scene}
	};
	
	std::ofstream file(SimpleEngine::Instance()->GetResourcesBaseDir() + path);
	if (file.is_open()) {
		file << std::setw(4) << gameState;
		file.close();
		return true;
	}
	return false;

}
bool SimpleEngine::DeserializeGameState(std::string path) {
	
	json gameState;
	std::ifstream file(SimpleEngine::Instance()->GetResourcesBaseDir() + path);
	if (file.is_open())
	{
		file >> gameState;
		file.close();
		_scene->Deserialize(gameState["scene"]);
		_gameLogic->Deserialize(gameState["gameLogic"]);
		return true;
	}
	return false;

}


std::string SimpleEngine::GetGameState() {
	json logic = _gameLogic->Serialize();
	json scene = _scene->Serialize();
	json gameState = {
		{ "gameLogic", logic },
		{ "scene", scene }
	};
	return gameState.dump(4);
}
bool SimpleEngine::SetGameState(std::string state) {
	json gameState = json::parse(state);
	
	//Create a new scene with no layers
	CreateScene();
	_scene->RemoveLayer(_scene->GetLayer(0));

	_scene->Deserialize(gameState["scene"]);
	_gameLogic->Deserialize(gameState["gameLogic"]);
	
	return true;

}