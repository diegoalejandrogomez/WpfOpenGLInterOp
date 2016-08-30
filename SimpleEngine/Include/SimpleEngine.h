#pragma once
#include "SimpleRenderer.h"
#include "SimpleScene.h"
#include "SimpleGameLogic.h"
#include "SimpleInput.h"
#include <chrono>
#include "SimpleConfiguration.h"

class SIMPLE_API SimpleEngine final{
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

	void SetResourcesBaseDir(std::string const& baseDir);
	std::string GetResourcesBaseDir() { return _resBaseDir; };
		
	void InitRenderer(HWND hWnd, uint32_t width, uint32_t height);
	void InitInput(HWND hWnd, bool exclusive);
	void SetGameLogic(SimpleGameLogic* _newGameMode);
	void CreateScene();

	//Getter
	inline SimpleScene* GetScene() { return _scene; }
	//Obtain current or next game logic
	inline SimpleGameLogic*  GetGameLogic() { return _gameLogic == nullptr? _nextGameLogic:_gameLogic; }
	inline SimpleRenderer* GetRenderer() { return _renderer; }
	inline SimpleInput* GetInput() { return _input; }
	inline float GetRenderFPS() const { return _renderTime.count() > 0? 1.0f / _renderTime.count() : 0; }
	inline float GetLogicFPS() const { return _renderTime.count() > 0?  1.0f / _logicTime.count(): 0; }

	//Used by external event loops
	void Render(float dt);
	void Advance(float dt);

	//Run an automatic event loop in the current thread
	//TODO
	void Run() {};

	void SerializeResources();
	void DeserializeResources();

	//We don't store type info into game logic, so it assumes that the 
	//user loads an appropiate file matching the loaded logic
	bool SerializeGameLogic(std::string const& path);
	bool DeserializeGameLogic(std::string const& path);
	std::string GetGameLogicState() const;
	void SetGameLogicState(std::string const& state);

	bool SerializeScene(std::string const& path);
	bool DeserializeScene(std::string const& path);
	std::string GetSceneState() const;
	bool SetSceneState(std::string const& state);

	bool SerializeGameState(std::string const& path);
	bool DeserializeGameState(std::string const& path);
	std::string GetGameState() const;
	bool SetGameState(std::string const& state);

	void UseInternalFrameTime(bool value) { _useInternalFrameTime = value; }
protected:
	SimpleEngine() {};
	~SimpleEngine() {};

	SimpleRenderer*	_renderer = nullptr;
	SimpleScene*	_scene = nullptr;
	SimpleGameLogic* _gameLogic = nullptr;
	SimpleGameLogic* _nextGameLogic = nullptr;
	SimpleInput*	_input;

	 //Instant frame time for logic and render update
	std::chrono::duration<float> _renderTime;
	std::chrono::duration<float> _logicTime;
	
	std::string _resBaseDir;

	bool _useInternalFrameTime = true;

	void _SwitchGameLogic();
};