#pragma once
#include "SimpleEngineNativeTileEditor.h"
#include "TileEditorApp.h"

extern "C" {
	TILEEDITOR_API TileEditorApp* TileEditorApp_Create();
	TILEEDITOR_API void TileEditorApp_Destroy(TileEditorApp* app);
	
	//Tile editor methods
	TILEEDITOR_API void NewMap();
	TILEEDITOR_API void LoadState(std::string gameState);
	TILEEDITOR_API std::string GetState();

	TILEEDITOR_API void SetMapSize(int width, int height);
	TILEEDITOR_API void SetMapWidth(int width);
	TILEEDITOR_API void SetMapHeight(int height);

	TILEEDITOR_API void TileEditorApp_SetCursorPosition(float x, float y);
	TILEEDITOR_API void TileEditorApp_SetCursorIdle();
	TILEEDITOR_API void TileEditorApp_SetCursorTile(const char* sheet, int index);

	TILEEDITOR_API void SetCursorErase();
	TILEEDITOR_API void Paint();

	TILEEDITOR_API int GetMapWidth();
	TILEEDITOR_API int GetMapHeight();

	TILEEDITOR_API json Serialize();
	TILEEDITOR_API bool Deserialize(json &node);
}