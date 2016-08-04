#include "stdafx.h"
#include "DebugGameLogic.h"
#include "SimpleDebugObject.h"
#include "SimpleEngine.h"
void DebugGameLogic::Init()
{

	SimpleDebugObject* obj = new SimpleDebugObject();
	SimpleEngine::Instance()->GetScene()->AddEntity(obj);
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
