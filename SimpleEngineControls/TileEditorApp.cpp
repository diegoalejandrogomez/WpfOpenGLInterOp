#include "stdafx.h"
#include "TileEditorApp.h"
#include "SimpleEngine.h"
#include "SimpleSpriteSheetRenderer.h"

void TileEditorApp::Init()
{

	SimpleEngine* engine = SimpleEngine::Instance();

	SetMapSize(10, 10);

	_tileMapLayer = new SimpleLayer();
	_tileMapLayer->SetZ(-1.0f);
	_tileMapLayer->SetName("MainTileMap");
	engine->GetScene()->AddLayer(_tileMapLayer);

	_uiLayer = new SimpleLayer();
	_uiLayer->SetZ(1000.0f);
	_uiLayer->SetName("UI");
	_uiLayer->SetQueryable(false);

	engine->GetScene()->AddLayer(_uiLayer);

	//Load cursor spritesheet
	engine->GetRenderer()->CreateSpriteSheet("media/grid.png");
	SimpleSpriteSheet *spriteSheet = engine->GetRenderer()->GetSpriteSheet("media/grid.png");
	spriteSheet->AddSpriteFrame({ 0,0 }, { spriteSheet->GetWidth(), spriteSheet->GetHeight() });
	
	SetCursorIdle();

}

void TileEditorApp::SetCursorPosition(float x, float y) {
	if(_cursor != nullptr)
		_cursor->SetPosition({ x, y, 0.0f });
}

void TileEditorApp::Paint() {
	
	//We SHOULD implement copy constructor/assignation operator
	if (_hasTile) {
		SimpleSpriteSheetRenderer *tile = new SimpleSpriteSheetRenderer();
		tile->SetSpriteSheet(_cursor->GetSpriteSheet());
		tile->SetIndex(_cursor->GetIndex());
		tile->SetSize({ 1.0f,1.0f });
		tile->SnapToGrid(true);
		tile->SetSnapGridSize({ 1.0f,1.0f });
		tile->SetPosition(_cursor->GetPosition());
		glm::vec3 pos = _cursor->GetPosition();
		int idx = _tileMapSize.x * int(pos.y) + (int)pos.x;
		_tiles[idx] = tile;
		SimpleEngine::Instance()->GetScene()->AddEntity(tile, "MainTileMap");
	}
}

void TileEditorApp::SetCursorIdle() {
	_hasTile = false;
	auto c = new SimpleSpriteSheetRenderer();
	c->SetSpriteSheet("media/grid.png");
	c->SetIndex(0);
	c->SetSize({ 1.0f, 1.0f });
	c->SnapToGrid(true);
	c->SetSnapGridSize({ 1.0f, 1.0f });
	_cursor = c;
	SimpleEngine::Instance()->GetScene()->AddEntity(_cursor, "UI");
	
}
void TileEditorApp::SetCursorTile(SimpleID sheet, int index) {
	_hasTile = true;

	if (_cursor != nullptr) {
		SimpleEngine::Instance()->GetScene()->RemoveEntity(_cursor);
		delete _cursor;
	}

	auto c = new SimpleSpriteSheetRenderer();
	c->SetSpriteSheet(sheet);
	c->SetIndex(index);
	c->SetSize({ 1, 1 });
	c->SnapToGrid(true);
	c->SetSnapGridSize({ 1, 1 });
	_cursor = c;
	SimpleEngine::Instance()->GetScene()->AddEntity(_cursor, "UI");

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
		delete _gridLayer;
	}

	_grid = new SimpleLineRenderer();
	_gridLayer = new SimpleLayer();
	_gridLayer->SetZ(-1000.0f);
	_gridLayer->AddEntity(_grid);
	_gridLayer->SetName("Grid");
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