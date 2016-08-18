#include "stdafx.h"
#include "TileEditorApp.h"
#include "SimpleEngine.h"
#include "SimpleSpriteSheetRenderer.h"
#include <filesystem>
//C++ 14/17 ... but why not XD
using namespace std::tr2::sys;

void TileEditorApp::Init()
{

	SimpleEngine* engine = SimpleEngine::Instance();
	engine->SetResourcesBaseDir("./temp/");
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

	//Copy resources to temp folder
	copy("./editorResources/media", "./temp/media/");

	//Load cursor spritesheet
	engine->GetRenderer()->CreateSpriteSheet("media/grid.png");
	SimpleSpriteSheet *spriteSheet = engine->GetRenderer()->GetSpriteSheet("media/grid.png");
	spriteSheet->AddSpriteFrame({ 0,0 }, { spriteSheet->GetWidth(), spriteSheet->GetHeight() });

	engine->GetRenderer()->CreateSpriteSheet("media/delete.png");
	spriteSheet = engine->GetRenderer()->GetSpriteSheet("media/delete.png");
	spriteSheet->AddSpriteFrame({ 0,0 }, { spriteSheet->GetWidth(), spriteSheet->GetHeight() });
	
	SetCursorIdle();

}

void TileEditorApp::SetCursorPosition(float x, float y) {
	if(_cursor != nullptr)
		_cursor->SetPosition({ x, y, 0.0f });
}

void TileEditorApp::Paint() {

	if (_hasTile)
		_Draw();

	if (_erasing)
		_Erase();
}

void TileEditorApp::_Draw() {
	
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


void TileEditorApp::_Erase() {

	glm::vec3 pos = _cursor->GetPosition();
	int idx = _tileMapSize.x * int(pos.y) + (int)pos.x;
	if (_tiles[idx] != nullptr) {
		SimpleEngine::Instance()->GetScene()->RemoveEntity(_tiles[idx], "MainTileMap");
		delete _tiles[idx];
		_tiles[idx] = nullptr;
	}

}

void TileEditorApp::SetCursorIdle() {
	
	_LoadCursor("media/grid.png", 0, "UI");
	_hasTile = false;
	_erasing = false;
}

void TileEditorApp::SetCursorErase() {

	_LoadCursor("media/delete.png", 0,"UI");
	_hasTile = false;
	_erasing = true;
}

void TileEditorApp::SetCursorTile(SimpleID sheet, int index) {
	_LoadCursor(sheet, index, "MainTileMap");
	_hasTile = true;
	_erasing = false;
}

void TileEditorApp::_LoadCursor(SimpleID sheet, int index, SimpleID layer) {

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
	SimpleEngine::Instance()->GetScene()->AddEntity(_cursor, layer);

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
	SimpleEngine::Instance()->GetScene()->GetCamera()->SetMaxVisibleArea(SimpleAABB({ 0.0f,0.0f }, _tileMapSize));

}


void TileEditorApp::SetMapWidth(int width) {
	

	_tileMapSize.x = width;
	_ResizeGrid();
	_CreateGrid();

	//Set camera working area
	SimpleEngine::Instance()->GetScene()->GetCamera()->SetMaxVisibleArea(SimpleAABB({ 0.0f,0.0f }, _tileMapSize));
	
}


void TileEditorApp::SetMapHeight(int height) {


	_tileMapSize.y = height;
	_ResizeGrid();
	_CreateGrid();
	SimpleEngine::Instance()->GetScene()->GetCamera()->SetMaxVisibleArea(SimpleAABB({ 0.0f,0.0f }, _tileMapSize));
	
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


//We could keep the added elements in the future... 
void TileEditorApp::_ResizeGrid() {

	//Remove all the tiles from the layer
	//SimpleEngine::Instance()->GetScene()->GetLayer("MainTileMap")->Clear(true);

	if (_tiles != nullptr)
		delete[] _tiles;
	int tileAmount = _tileMapSize.x * _tileMapSize.y;
	_tiles = new SimpleSpriteRenderer*[tileAmount];
	memset(_tiles, 0, tileAmount * sizeof(SimpleSpriteRenderer*));

	//Reinsert the entities that still fit in the grid
	std::vector<SimpleSpriteRenderer*> _toErase;

	SimpleLayer* _tileLayer = SimpleEngine::Instance()->GetScene()->GetLayer("MainTileMap");
	for (auto e : _tileLayer->GetEntities()) {
		//Compute position
		glm::ivec3 iPos = e->GetPosition();
		if (iPos.x >= _tileMapSize.x || iPos.x < 0 || iPos.y >= _tileMapSize.y || iPos.y < 0)
			_toErase.push_back(static_cast<SimpleSpriteRenderer*>(e));
		else {
			int idx = _tileMapSize.x * iPos.y + iPos.x;
			_tiles[idx] = static_cast<SimpleSpriteRenderer*>(e);
		}

	}

	for (auto e : _toErase) {
		_tileLayer->RemoveEntity(e);
		delete e;
	}


}