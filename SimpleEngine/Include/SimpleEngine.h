#pragma once
#include "SimpleRenderer.h"
#include "SimpleScene.h"
#include "SimpleGamemode.h"

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
	void SetGameMode(SimpleGameMode* _newGameMode);
	void CreateScene();

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

	SimpleRenderer * _renderer = nullptr;
	SimpleScene* _scene = nullptr;
	SimpleGameMode* _gameMode = nullptr;
	SimpleGameMode* _nextGameMode = nullptr;

	void _SwitchGameMode();
};