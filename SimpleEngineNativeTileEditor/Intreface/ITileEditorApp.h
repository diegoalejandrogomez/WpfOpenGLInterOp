#pragma once
#include "SimpleEngineNativeTileEditor.h"
#include "TileEditorApp.h"

extern "C" {
	TILEEDITOR_API TileEditorApp* TileEditorApp_Create();
	TILEEDITOR_API void TileEditorApp_Destroy(TileEditorApp* app);
	
	TILEEDITOR_API void TileEditorApp_SetCursorPosition(float x, float y);
	TILEEDITOR_API void TileEditorApp_SetCursorIdle();
	TILEEDITOR_API void TileEditorApp_SetCursorTile(const char* sheet, int index);
}