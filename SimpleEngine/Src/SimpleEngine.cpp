#include "stdafx.h"
#include "SimpleEngine.h"
#include "DebugRenderPass.h"
#include "SimpleObjectsRenderPass.h"
#include "SimpleDispatcher.h"
#include "DebugGameLogic.h"
void SimpleEngine::InitRenderer(HWND hWnd, uint32_t width, uint32_t height) {
	
	_renderer = new SimpleRenderer();
	_renderer->InitializeOpenGL(hWnd, width, height);

	_renderer->AddPass(new DebugRenderPass());
	_renderer->AddPass(new SimpleObjectsRenderPass());
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

	if (_gameLogic != nullptr)
		_gameLogic->Shutdown();

	_gameLogic = _nextGameLogic;
	if (_gameLogic != nullptr) { //Could be switching to nullptr
		_gameLogic->Init();
		_nextGameLogic = nullptr;
	}

}

void SimpleEngine::Render(float dt) {
	
	SIMPLE_ASSERT(_renderer != nullptr);
		
	_renderer->Render(dt, _scene);
}

void SimpleEngine::Advance(float dt) {
	
	//Check if we must switch the game mode
	if (_nextGameLogic != nullptr)
		_SwitchGameLogic();

	if (_gameLogic != nullptr && _gameLogic->IsRunning()) {
		_gameLogic->Advance(dt);
		if (_scene != nullptr)
			_scene->Advance(dt);
	}

	//Flush pending events
	SimpleDispatcher::Instance()->Flush();
}

#define DEBUG_CONTENT
void SimpleEngine::Initialize() {

	SIMPLE_ASSERT(_renderer != nullptr);

	//Loads a default scene
	CreateScene();
	_scene->GetCamera()->SetViewportSize((float)_renderer->GetWidth(), (float)_renderer->GetHeight());

#ifdef DEBUG_CONTENT
	SetGameLogic(new DebugGameLogic());
#endif

}
void SimpleEngine::Shutdown() {


}
