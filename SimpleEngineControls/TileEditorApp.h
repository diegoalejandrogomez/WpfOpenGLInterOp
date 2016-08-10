#pragma once
#include "SimpleGameLogic.h"
#include "SimpleRenderer.h"
#include "SimpleLayer.h"
#include "SimpleSpriteRenderer.h"
#include "SimpleLineRenderer.h"

class TileEditorApp : public SimpleGameLogic{
	
public:
	// Inherited via SimpleGameLogic
	virtual void Init() override;
	virtual void Advance(float dt) override;
	virtual void Shutdown() override;
	virtual bool IsRunning() override;

	//Tile editor methods
	void SetMapSize(int width, int height);	
	void SetMapWidth(int width);
	void SetMapHeight(int height);

	void SetCursorPosition(float x, float y);

	inline int  GetMapWidth()const { return _tileMapSize.x; }
	inline int  GetMapHeight()const { return _tileMapSize.y; }

private:

	void _CreateGrid();
	void _ResizeGrid();

	//We should have a SimpleObject for the whole tileset... but let's do this for now...
	SimpleLayer*			_gridLayer	= nullptr;
	SimpleLineRenderer*		_grid		= nullptr;
	SimpleLayer*			_uiLayer	= nullptr;
	SimpleSpriteRenderer*	_cursor		= nullptr;
	SimpleLayer*			_tileMapLayer = nullptr;
	glm::ivec2				_tileMapSize = glm::ivec2(0);
	SimpleSpriteRenderer**	_tiles = nullptr;

	
};

