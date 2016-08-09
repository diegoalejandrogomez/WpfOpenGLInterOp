#pragma once
#include "SimpleGameLogic.h"

class TileEditorApp : public SimpleGameLogic{
	
	// Inherited via SimpleGameLogic
	virtual void Init() override;
	virtual void Advance(float dt) override;
	virtual void Shutdown() override;
	virtual bool IsRunning() override;
};
