#pragma once
#include "SimpleGameLogic.h"
#include "SimpleRenderer.h"
#include "SimpleLayer.h"
#include "SimpleSpriteRenderer.h"

class TileEditorApp : public SimpleGameLogic{
	
public:
	// Inherited via SimpleGameLogic
	virtual void Init() override;
	virtual void Advance(float dt) override;
	virtual void Shutdown() override;
	virtual bool IsRunning() override;

	//Tile editor methods
	void SetMapSize(int width, int height);	

private:
	//We should have a SimpleObject for the whole tileset... but let's do this for now...
	SimpleLayer*			_tileMapLayer = nullptr;
	glm::ivec2				_tileMapSize = glm::ivec2(0);
	SimpleSpriteRenderer**	_tiles = nullptr;

	
};
