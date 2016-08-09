#include "stdafx.h"
#include "TileEditorApp.h"

void TileEditorApp::Init()
{
	_tileMapLayer = new SimpleLayer();
	_tileMapLayer->SetZ(-1.0f);
}

void TileEditorApp::Advance(float dt)
{
	
}

void TileEditorApp::Shutdown()
{
}

bool TileEditorApp::IsRunning()
{
	return true;
}

void TileEditorApp::SetMapSize(int width, int height) {
	if (_tiles != nullptr)
		delete[] _tiles;
	
	_tileMapSize.x = width;
	_tileMapSize.y = height;

	int tileAmount = _tileMapSize.x * _tileMapSize.y;
	_tiles = new SimpleSpriteRenderer*[tileAmount];
	memset(_tiles, 0, tileAmount * sizeof(SimpleSpriteRenderer*));
}