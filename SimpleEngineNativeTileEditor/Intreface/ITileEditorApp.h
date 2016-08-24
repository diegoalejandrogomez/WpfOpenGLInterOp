#pragma once
#include "SimpleEngineNativeTileEditor.h"
#include "TileEditorApp.h"

extern "C" {
	TILEEDITOR_API TileEditorApp* TileEditorApp_Create();
	TILEEDITOR_API void TileEditorApp_Destroy(TileEditorApp* app);
	
	//Tile editor methods
	TILEEDITOR_API void TileEditorApp_NewMap();
	TILEEDITOR_API void TileEditorApp_LoadState(std::string gameState);
	TILEEDITOR_API const char*  TileEditorApp_GetState();

	TILEEDITOR_API void TileEditorApp_SetMapSize(int width, int height);
	TILEEDITOR_API void TileEditorApp_SetMapWidth(int width);
	TILEEDITOR_API void TileEditorApp_SetMapHeight(int height);

	TILEEDITOR_API void TileEditorApp_SetCursorPosition(float x, float y);
	TILEEDITOR_API void TileEditorApp_SetCursorIdle();
	TILEEDITOR_API void TileEditorApp_SetCursorTile(const char* sheet, int index);

	TILEEDITOR_API void TileEditorApp_SetCursorErase();
	TILEEDITOR_API void TileEditorApp_Paint();

	TILEEDITOR_API int TileEditorApp_GetMapWidth();
	TILEEDITOR_API int TileEditorApp_GetMapHeight();

	//Not available in C
	/*TILEEDITOR_API json TileEditorApp_Serialize();
	TILEEDITOR_API bool TileEditorApp_Deserialize(json &node);*/
}