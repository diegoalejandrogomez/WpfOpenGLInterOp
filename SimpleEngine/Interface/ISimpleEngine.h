#pragma once
#include "SimpleEngine.h"
#include "SimpleConfiguration.h"

extern "C" {

	SIMPLE_API SimpleEngine* SimpleEngine_Instance();
		
	SIMPLE_API void SimpleEngine_InitRenderer(HWND hWnd, uint32_t width, uint32_t height);

	SIMPLE_API void SimpleEngine_InitInput(HWND hWnd, bool exclusive);

	SIMPLE_API void SimpleEngine_Initialize();

	SIMPLE_API void SimpleEngine_SetGameLogic(SimpleGameLogic* logic);

	SIMPLE_API SimpleRenderer* SimpleEngine_GetRenderer();

	SIMPLE_API void  SimpleEngine_Shutdown();

	SIMPLE_API void SimpleEngine_SetResourcesBaseDir(const char* baseDir);

	SIMPLE_API const char* SimpleEngine_GetResourcesBaseDir();

	SIMPLE_API void SimpleEngine_CreateScene();

	SIMPLE_API SimpleScene* SimpleEngine_GetScene();

	SIMPLE_API SimpleGameLogic*  SimpleEngine_GetGameLogic();

	SIMPLE_API SimpleInput* SimpleEngine_GetInput();

	SIMPLE_API float SimpleEngine_GetRenderFPS();

	SIMPLE_API float SimpleEngine_GetLogicFPS();

	SIMPLE_API void SimpleEngine_Render(float dt);

	SIMPLE_API void SimpleEngine_Advance(float dt);

	SIMPLE_API void SimpleEngine_SerializeResources();

	SIMPLE_API void SimpleEngine_DeserializeResources();

	SIMPLE_API bool SimpleEngine_SerializeGameLogic(const char* path);

	SIMPLE_API bool SimpleEngine_DeserializeGameLogic(const char* path);

	SIMPLE_API void SimpleEngine_GetGameLogicState(char* state, int maxSize);

	SIMPLE_API void SimpleEngine_SetGameLogicState(const char* state);

	SIMPLE_API bool SimpleEngine_SerializeScene(const char* path);

	SIMPLE_API bool SimpleEngine_DeserializeScene(const char* path);

	SIMPLE_API void SimpleEngine_GetSceneState(char* state, int maxSize);

	SIMPLE_API void SimpleEngine_SetSceneState(const char* state);

	SIMPLE_API bool SimpleEngine_SerializeGameState(const char* path);

	SIMPLE_API bool SimpleEngine_DeserializeGameState(const char* path);

	SIMPLE_API void SimpleEngine_GetGameState(char* state, int maxSize);

	SIMPLE_API void SimpleEngine_SetGameState(const char* state);

}