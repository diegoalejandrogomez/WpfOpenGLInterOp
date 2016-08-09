#include "stdafx.h"
#include "SimpleEngine.h"
#include "DebugRenderPass.h"
#include "SimpleObjectsRenderPass.h"
#include "SimpleDispatcher.h"
#include "DebugGameLogic.h"
using namespace std::chrono;

void SimpleEngine::InitRenderer(HWND hWnd, uint32_t width, uint32_t height) {
	
	_renderer = new SimpleRenderer();
	_renderer->InitializeOpenGL(hWnd, width, height);

	_renderer->AddPass(new DebugRenderPass());
	_renderer->AddPass(new SimpleObjectsRenderPass());
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

	//Internal fps measuring
	static high_resolution_clock::time_point prev = high_resolution_clock::now();
	high_resolution_clock::time_point current = high_resolution_clock::now();
	_renderTime = duration_cast<nanoseconds>(current - prev);
	prev = current;
	
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

//#define DEBUG_CONTENT
void SimpleEngine::Initialize() {

	SIMPLE_ASSERT(_renderer != nullptr);
	SIMPLE_ASSERT(_input != nullptr);
	

	//Loads a default scene
	CreateScene();
	_scene->GetCamera()->SetViewportSize((float)_renderer->GetWidth(), (float)_renderer->GetHeight());

#ifdef DEBUG_CONTENT
	SetGameLogic(new DebugGameLogic());
#endif

}
void SimpleEngine::Shutdown() {


}
