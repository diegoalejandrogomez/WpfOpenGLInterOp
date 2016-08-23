#include "stdafx.h"
#include "ITileEditorApp.h"
#include "SimpleEngine.h"

TileEditorApp* TileEditorApp_Create() {
	return new TileEditorApp();
}


void TileEditorApp_Destroy(TileEditorApp* app) {
	delete app;
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