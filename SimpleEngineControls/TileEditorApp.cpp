#include "stdafx.h"
#include "TileEditorApp.h"
#include "SimpleEngine.h"

void TileEditorApp::Init()
{

	SetMapSize(10, 10);

	_tileMapLayer = new SimpleLayer();
	_tileMapLayer->SetZ(-1.0f);
}

void TileEditorApp::Advance(float dt)
{
	//SimpleEngine::Instance()->GetScene()->GetCamera()->ZoomToArea(SimpleAABB({ 0.0f,0.0f }, _tileMapSize));
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

	_CreateGrid();

	//SimpleEngine::Instance()->GetScene()->GetCamera()->ZoomToArea(SimpleAABB({ 0.0f,0.0f }, _tileMapSize));
}


void TileEditorApp::SetMapWidth(int width) {
	

	_tileMapSize.x = width;
	_ResizeGrid();
	_CreateGrid();

	//SimpleEngine::Instance()->GetScene()->GetCamera()->ZoomToArea(SimpleAABB({ 0.0f,0.0f }, _tileMapSize));
}


void TileEditorApp::SetMapHeight(int height) {


	_tileMapSize.y = height;
	_ResizeGrid();
	_CreateGrid();

	//SimpleEngine::Instance()->GetScene()->GetCamera()->ZoomToArea(SimpleAABB({ 0.0f,0.0f }, _tileMapSize));
}

void TileEditorApp::_CreateGrid() {
	//This approach introduces a lot of alias. Kept here for reference for now...
	
	if (_gridLayer != nullptr) {
		SimpleEngine::Instance()->GetScene()->RemoveLayer(_gridLayer);
		delete _grid;
		delete _gridLayer;
	}

	_grid = new SimpleLineRenderer();
	_gridLayer = new SimpleLayer();
	_gridLayer->SetZ(-1000.0f);
	_gridLayer->AddEntity(_grid);
	SimpleEngine::Instance()->GetScene()->AddLayer(_gridLayer);
	
	//Unitary tiles
	for (int i = 0; i <= _tileMapSize.x; ++i) 
		_grid->AddLine({ i,0 }, { i, _tileMapSize.y }, { 1.0f,1.0f,1.0f });
	for (int j = 0; j <= _tileMapSize.y; ++j) 	
		_grid->AddLine({ 0, j }, { _tileMapSize.x, j }, { 1.0f,1.0f,1.0f });

	_grid->Flush();
}


void TileEditorApp::_ResizeGrid() {

	if (_tiles != nullptr)
		delete[] _tiles;
	int tileAmount = _tileMapSize.x * _tileMapSize.y;
	_tiles = new SimpleSpriteRenderer*[tileAmount];
	memset(_tiles, 0, tileAmount * sizeof(SimpleSpriteRenderer*));

}