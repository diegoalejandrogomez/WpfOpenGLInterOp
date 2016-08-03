#include "stdafx.h"
#include "SimpleEngine.h"
#include "DebugRenderPass.h"
#include "SimpleObjectsRenderPass.h"

void SimpleEngine::InitRenderer(HWND hWnd, uint32_t width, uint32_t height) {
	
	_renderer = new SimpleRenderer();
	_renderer->InitializeOpenGL(hWnd, width, height);

	_renderer->AddPass(new DebugRenderPass());
	_renderer->AddPass(new SimpleObjectsRenderPass());
}

void SimpleEngine::SetGameMode(SimpleGameMode* _newGameMode) {

	_nextGameMode = _newGameMode;
}

void SimpleEngine::CreateScene() {
	if (_scene != nullptr) 
		delete _scene;
	_scene = new SimpleScene();
}
void SimpleEngine::_SwitchGameMode() {

	if (_gameMode != nullptr)
		_gameMode->Shutdown();

	_gameMode = _nextGameMode;
	if (_gameMode != nullptr) { //Could be switching to nullptr
		_gameMode->Init();
		_nextGameMode = nullptr;
	}

}

void SimpleEngine::Render(float dt) {
	
	SIMPLE_ASSERT(_renderer != nullptr);
		
	_renderer->Render(dt, _scene);
}

void SimpleEngine::Advance(float dt) {
	
	//Check if we must switch the game mode
	if (_nextGameMode != nullptr)
		_SwitchGameMode();

	if (_gameMode != nullptr && _gameMode->IsRunning()) {
		_gameMode->Advance(dt);
		if (_scene != nullptr)
			_scene->Advance(dt);
	}

}

void SimpleEngine::Initialize() {

	SIMPLE_ASSERT(_renderer != nullptr);

	//Loads a default scene
	CreateScene();
	_scene->GetCamera()->SetViewportSize((float)_renderer->GetWidth(), (float)_renderer->GetHeight());

}
void SimpleEngine::Shutdown() {


}
