#pragma once
#include "SimpleRenderer.h"
#include "SimpleScene.h"
#include "SimpleGameLogic.h"

class SimpleEngine final{
public:

	static SimpleEngine*  Instance()
	{
		static SimpleEngine instance;
		return &instance;
	}

	// delete copy and move constructors and assign operators
	SimpleEngine(SimpleEngine const&) = delete;             // Copy construct
	SimpleEngine(SimpleEngine&&) = delete;                  // Move construct
	SimpleEngine& operator=(SimpleEngine const&) = delete;  // Copy assign
	SimpleEngine& operator=(SimpleEngine &&) = delete;      // Move assign

	void Initialize();
	void Shutdown();
	
	void InitRenderer(HWND hWnd, uint32_t width, uint32_t height);
	void SetGameLogic(SimpleGameLogic* _newGameMode);
	void CreateScene();

	//Getter
	SimpleScene* GetScene() { return _scene; ; }
	SimpleRenderer* GetRenderer() { return _renderer; };

	//Used by external event loops
	void Render(float dt);
	void Advance(float dt);

	//Run an automatic event loop in the current thread
	//TODO
	void Run() {};

protected:
	SimpleEngine() {};
	~SimpleEngine() {};

	SimpleRenderer*	_renderer = nullptr;
	SimpleScene*	_scene = nullptr;
	SimpleGameLogic* _gameLogic = nullptr;
	SimpleGameLogic* _nextGameLogic = nullptr;

	void _SwitchGameLogic();
};