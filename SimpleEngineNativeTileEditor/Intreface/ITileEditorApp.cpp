#include "stdafx.h"
#include "ITileEditorApp.h"
#include "SimpleEngine.h"

TileEditorApp* TileEditorApp_Create() {
	return new TileEditorApp();
}


void TileEditorApp_Destroy(TileEditorApp* app) {
	delete app;
}

TILEEDITOR_API void NewMap()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		app->NewMap();
}

TILEEDITOR_API void LoadState(std::string gameState)
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		app->LoadState(gameState);
}

TILEEDITOR_API std::string GetState()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->GetState();

	return nullptr;
}

TILEEDITOR_API void SetMapSize(int width, int height)
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->SetMapSize(width, height);
}

TILEEDITOR_API void SetMapWidth(int width)
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->SetMapWidth(width);
}

TILEEDITOR_API void SetMapHeight(int height)
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

TILEEDITOR_API void SetCursorErase()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->SetCursorErase();
}

TILEEDITOR_API void Paint()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->Paint();
}

TILEEDITOR_API int GetMapWidth()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->GetMapWidth();
}

TILEEDITOR_API int GetMapHeight()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->GetMapHeight();
}

TILEEDITOR_API json Serialize()
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->Serialize();
}

TILEEDITOR_API bool Deserialize(json & node)
{
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	if (app != nullptr)
		return app->Deserialize(node);
}

