#include "stdafx.h"
#include "ITileEditorApp.h"
#include "SimpleEngine.h"

TileEditorApp* TileEditorApp_Create() {
	return new TileEditorApp();
}


void TileEditorApp_Destroy(TileEditorApp* app) {
	delete app;
}

TILEEDITOR_API void TileEditorApp_NewMap()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		app->NewMap();
}

TILEEDITOR_API void TileEditorApp_LoadState(std::string gameState)
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		app->LoadState(gameState);
}

TILEEDITOR_API const char* TileEditorApp_GetState()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->GetState().c_str();

	return nullptr;
}

TILEEDITOR_API void TileEditorApp_SetMapSize(int width, int height)
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->SetMapSize(width, height);
}

TILEEDITOR_API void TileEditorApp_SetMapWidth(int width)
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->SetMapWidth(width);
}

TILEEDITOR_API void TileEditorApp_SetMapHeight(int height)
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->SetMapHeight(height);
}


void TileEditorApp_SetCursorPosition(float x, float y) {
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		app->SetCursorPosition(x, y);

}
void TileEditorApp_SetCursorIdle() {
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		app->SetCursorIdle();

}

void TileEditorApp_SetCursorTile(const char* sheet, int index) {
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		app->SetCursorTile(sheet, index);
}

TILEEDITOR_API void TileEditorApp_SetCursorErase()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->SetCursorErase();
}

TILEEDITOR_API void TileEditorApp_Paint()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->Paint();
}

TILEEDITOR_API int TileEditorApp_GetMapWidth()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->GetMapWidth();
	return 0;
}

TILEEDITOR_API int TileEditorApp_GetMapHeight()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->GetMapHeight();
	return 0;
}

TILEEDITOR_API void SetCursorAnimated(const char* animationName) {
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		app->SetCursorAnimated(animationName);
}