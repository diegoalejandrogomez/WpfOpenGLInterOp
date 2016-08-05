#include "stdafx.h"
#include "DebugGameLogic.h"
#include "SimpleDebugObject.h"
#include "SimpleEngine.h"
#include "SimpleLayer.h"
#include "SimpleSpriteRenderer.h"

void DebugGameLogic::Init()
{

	SimpleLayer* layer = new SimpleLayer();
	SimpleEngine::Instance()->GetScene()->AddLayer(layer);
	
	//SimpleDebugObject* obj = new SimpleDebugObject();
	//SimpleEngine::Instance()->GetScene()->AddEntity(obj, layer);

	SimpleSpriteRenderer * sprite = new SimpleSpriteRenderer();
	sprite->SetAsTexture("./media/spriteFull.png");
	sprite->SetSize(glm::vec2(200, 200));
	SimpleEngine::Instance()->GetScene()->AddEntity(sprite, layer);

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
