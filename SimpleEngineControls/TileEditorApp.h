#pragma once
#include "SimpleGameLogic.h"
#include "SimpleRenderer.h"
#include "SimpleLayer.h"
#include "SimpleSpriteRenderer.h"
#include "SimpleLineRenderer.h"
#include "SimpleSpriteSheetRenderer.h"
#include "json.hpp"
using json = nlohmann::json;

class TileEditorApp : public SimpleGameLogic{
	
public:
	// Inherited via SimpleGameLogic
	virtual void Init() override;
	virtual void Advance(float dt) override;
	virtual void Shutdown() override;
	virtual bool IsRunning() override;

	//Tile editor methods
	void NewMap();
	void LoadState(std::string gameState);
	std::string GetState();

	void SetMapSize(int width, int height);	
	void SetMapWidth(int width);
	void SetMapHeight(int height);

	void SetCursorPosition(float x, float y);
	void SetCursorIdle();
	void SetCursorTile(SimpleID sheet, int index);
	void SetCursorAnimated(SimpleID animationName);
	void SetCursorErase();
	void Paint();
	

	inline int  GetMapWidth()const { return _tileMapSize.x; }
	inline int  GetMapHeight()const { return _tileMapSize.y; }

	json Serialize() override;
	bool Deserialize(const json &node, std::string dir) override;
	bool Deserialize(const json &node) override;
private:

	void _CreateGrid();
	void _ResizeGrid();
	void _LoadCursor(SimpleID sheet, int index, SimpleID layer);
	void _Erase();
	void _Draw();
	void _CreateSceneStructure();

	//We should have a SimpleObject for the whole tileset... but let's do this for now...
	SimpleLayer*				_gridLayer	= nullptr;
	SimpleLineRenderer*			_grid		= nullptr;
	SimpleLayer*				_uiLayer	= nullptr;
	SimpleObject*	_cursor		= nullptr;
	SimpleLayer*				_tileMapLayer = nullptr;
	glm::ivec2					_tileMapSize = glm::ivec2(0);
	SimpleObject**				_tiles = nullptr;
	bool						_hasTile = false;
	bool						_erasing = false;
	bool						_animated = false;

	
};

