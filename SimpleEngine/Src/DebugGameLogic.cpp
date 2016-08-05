#include "stdafx.h"
#include "DebugGameLogic.h"
#include "SimpleDebugObject.h"
#include "SimpleEngine.h"
#include "SimpleLayer.h";

void DebugGameLogic::Init()
{

	SimpleDebugObject* obj = new SimpleDebugObject();
	SimpleLayer* layer = new SimpleLayer();
	SimpleEngine::Instance()->GetScene()->AddLayer(layer);
	SimpleEngine::Instance()->GetScene()->AddEntity(obj, layer);
}

void DebugGameLogic::Advance(float dt)
{
}

void DebugGameLogic::Shutdown()
{
}

bool DebugGameLogic::IsRunning()
{
	return false;
}
