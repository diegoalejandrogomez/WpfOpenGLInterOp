#pragma once
#include "SimpleRenderer.h"
#include "SimpleScene.h"
#include "SimpleGameLogic.h"
#include "SimpleInput.h"

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
	inline SimpleScene* GetScene() { return _scene; ; }
	inline SimpleRenderer* GetRenderer() { return _renderer; };
	inline SimpleInput* GetInput() { return _input; };
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
	SimpleInput*	_input;

	void _SwitchGameLogic();
};