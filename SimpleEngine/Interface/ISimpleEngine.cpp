#include "stdafx.h"
#include "SimpleEngine.h"
#include "SimpleConfiguration.h"

SimpleEngine* SimpleEngine_Instance() {
	return SimpleEngine::Instance();
}

void SimpleEngine_InitRenderer(HWND hWnd, uint32_t width, uint32_t height) {
	SimpleEngine::Instance()->InitRenderer(hWnd, width, height);
}

void SimpleEngine_InitInput(HWND hWnd, bool exclusive) {
	SimpleEngine::Instance()->InitInput(hWnd, exclusive);
}

void SimpleEngine_Initialize() {
	SimpleEngine::Instance()->Initialize();
}

void SimpleEngine_SetGameLogic(SimpleGameLogic* logic) {
	SimpleEngine::Instance()->SetGameLogic(logic);
}

SimpleRenderer* SimpleEngine_GetRenderer() {
	SimpleEngine* eng = SimpleEngine::Instance();
	return eng->GetRenderer();
}

	
void  SimpleEngine_Shutdown() {
	SimpleEngine::Instance()->Shutdown();
}

void SimpleEngine_SetResourcesBaseDir(const char* baseDir) {
	SimpleEngine::Instance()->SetResourcesBaseDir(baseDir);
}
	
const char* SimpleEngine_GetResourcesBaseDir() {
	return SimpleEngine::Instance()->GetResourcesBaseDir().c_str(); 
};
	
void SimpleEngine_CreateScene() {
	SimpleEngine::Instance()->CreateScene();
}

SimpleScene* SimpleEngine_GetScene() { return SimpleEngine::Instance()->GetScene(); }

SimpleGameLogic*  SimpleEngine_GetGameLogic() { 
	return SimpleEngine::Instance()->GetGameLogic();
};

SimpleInput* SimpleEngine_GetInput() { return SimpleEngine::Instance()->GetInput(); }

float SimpleEngine_GetRenderFPS() { return SimpleEngine::Instance()->GetRenderFPS(); }

float SimpleEngine_GetLogicFPS() { return SimpleEngine::Instance()->GetLogicFPS(); }
	
void SimpleEngine_Render(float dt) {
	SimpleEngine::Instance()->Render(dt);
}

void SimpleEngine_Advance(float dt) {
	SimpleEngine::Instance()->Advance(dt);	
}

void SimpleEngine_SerializeResources() {
	SimpleEngine::Instance()->SerializeResources();
}

void SimpleEngine_DeserializeResources() {
	SimpleEngine::Instance()->DeserializeResources();
}
	
bool SimpleEngine_SerializeGameLogic(const char* path) {
	return SimpleEngine::Instance()->SerializeGameLogic(path);
}

bool SimpleEngine_DeserializeGameLogic(const char* path) {
	return SimpleEngine::Instance()->DeserializeGameLogic(path);
}

const char* SimpleEngine_GetGameLogicState() {
	return SimpleEngine::Instance()->GetGameLogicState().c_str();
}
void SimpleEngine_SetGameLogicState(const char* state) {
	SimpleEngine::Instance()->SetGameLogicState(state);
}

bool SimpleEngine_SerializeScene(const char* path) {
	return SimpleEngine::Instance()->SerializeScene(path);
}

bool SimpleEngine_DeserializeScene(const char* path) {
	return SimpleEngine::Instance()->DeserializeScene(path);
}

const char* SimpleEngine_GetSceneState() {
	return SimpleEngine::Instance()->GetSceneState().c_str();
}
	
void SimpleEngine_SetSceneState(const char* state) {
	SimpleEngine::Instance()->SetSceneState(state);
}


bool SimpleEngine_SerializeGameState(const char* path) {
	return SimpleEngine::Instance()->SerializeGameState(path);
}

bool SimpleEngine_DeserializeGameState(const char* path) {
	return SimpleEngine::Instance()->DeserializeGameState(path);
}
	

const char* SimpleEngine_GetGameState() {
	return SimpleEngine::Instance()->GetGameState().c_str();
}

void SimpleEngine_SetGameState(const char* state) {
	SimpleEngine::Instance()->SetGameState(state);
}
	
