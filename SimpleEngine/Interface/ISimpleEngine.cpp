#include "stdafx.h"
#include "SimpleEngine.h"
#include "SimpleConfiguration.h"

extern "C" {

	SIMPLE_API SimpleEngine* SimpleEngine_Instance() {
		return SimpleEngine::Instance();
	}

	SIMPLE_API void SimpleEngine_InitRenderer(HWND hWnd, uint32_t width, uint32_t height) {
		SimpleEngine::Instance()->InitRenderer(hWnd, width, height);
	}

	SIMPLE_API void SimpleEngine_InitInput(HWND hWnd, bool exclusive) {
		SimpleEngine::Instance()->InitInput(hWnd, exclusive);
	}

	SIMPLE_API void SimpleEngine_Initialize() {
		SimpleEngine::Instance()->Initialize();
	}

	SIMPLE_API void SimpleEngine_SetGameLogic(SimpleGameLogic* logic) {
		SimpleEngine::Instance()->SetGameLogic(logic);
	}

	SIMPLE_API SimpleRenderer* SimpleEngine_GetRenderer() {
		SimpleEngine* eng = SimpleEngine::Instance();
		return eng->GetRenderer();
	}


	SIMPLE_API void  SimpleEngine_Shutdown() {
		SimpleEngine::Instance()->Shutdown();
	}

	SIMPLE_API void SimpleEngine_SetResourcesBaseDir(const char* baseDir) {
		SimpleEngine::Instance()->GetResourceManager()->SetResourcesBaseDir(baseDir);
	}

	SIMPLE_API const char* SimpleEngine_GetResourcesBaseDir() {
		return SimpleEngine::Instance()->GetResourceManager()->GetResourcesBaseDir().c_str();
	};

	SIMPLE_API void SimpleEngine_CreateScene() {
		SimpleEngine::Instance()->CreateScene();
	}

	SIMPLE_API SimpleScene* SimpleEngine_GetScene() { return SimpleEngine::Instance()->GetScene(); }

	SIMPLE_API SimpleGameLogic*  SimpleEngine_GetGameLogic() {
		return SimpleEngine::Instance()->GetGameLogic();
	};

	SIMPLE_API SimpleInput* SimpleEngine_GetInput() { return SimpleEngine::Instance()->GetInput(); }

	SIMPLE_API float SimpleEngine_GetRenderFPS() { return SimpleEngine::Instance()->GetRenderFPS(); }

	SIMPLE_API float SimpleEngine_GetLogicFPS() { return SimpleEngine::Instance()->GetLogicFPS(); }

	SIMPLE_API void SimpleEngine_Render(float dt) {
		SimpleEngine::Instance()->Render(dt);
	}

	SIMPLE_API void SimpleEngine_Advance(float dt) {
		SimpleEngine::Instance()->Advance(dt);
	}

	SIMPLE_API void SimpleEngine_SerializeResources() {
		SimpleEngine::Instance()->SerializeResources();
	}

	SIMPLE_API void SimpleEngine_DeserializeResources() {
		SimpleEngine::Instance()->DeserializeResources();
	}

	SIMPLE_API bool SimpleEngine_SerializeGameLogic(const char* path) {
		return SimpleEngine::Instance()->SerializeGameLogic(path);
	}

	SIMPLE_API bool SimpleEngine_DeserializeGameLogic(const char* path) {
		return SimpleEngine::Instance()->DeserializeGameLogic(path);
	}

	SIMPLE_API void SimpleEngine_GetGameLogicState(char* state, int maxSize) {
		strcpy_s(state, maxSize, SimpleEngine::Instance()->GetGameLogicState().c_str());		
	}
	SIMPLE_API void SimpleEngine_SetGameLogicState(const char* state) {
		SimpleEngine::Instance()->SetGameLogicState(state);
	}

	SIMPLE_API bool SimpleEngine_SerializeScene(const char* path) {
		return SimpleEngine::Instance()->SerializeScene(path);
	}

	SIMPLE_API bool SimpleEngine_DeserializeScene(const char* path) {
		return SimpleEngine::Instance()->DeserializeScene(path);
	}

	SIMPLE_API void SimpleEngine_GetSceneState(char* state, int maxSize) {
		strcpy_s(state, maxSize, SimpleEngine::Instance()->GetSceneState().c_str());
	
	}

	SIMPLE_API void SimpleEngine_SetSceneState(const char* state) {
		SimpleEngine::Instance()->SetSceneState(state);
	}


	SIMPLE_API bool SimpleEngine_SerializeGameState(const char* path) {
		return SimpleEngine::Instance()->SerializeGameState(path);
	}

	SIMPLE_API bool SimpleEngine_DeserializeGameState(const char* path) {
		return SimpleEngine::Instance()->DeserializeGameState(path);
	}


	SIMPLE_API void SimpleEngine_GetGameState(char* state, int maxSize) {
		strcpy_s(state, maxSize, SimpleEngine::Instance()->GetGameState().c_str());
	}

	SIMPLE_API void SimpleEngine_SetGameState(const char* state) {
		SimpleEngine::Instance()->SetGameState(state);
	}

}