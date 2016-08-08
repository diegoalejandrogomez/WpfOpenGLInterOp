#include "stdafx.h"
#include "DebugGameLogic.h"
#include "SimpleDebugObject.h"
#include "SimpleEngine.h"
#include "SimpleLayer.h"
#include "SimpleSpriteRenderer.h"

void DebugGameLogic::Init()
{

	SimpleLayer* layer = new SimpleLayer();
	layer->SetZ(SimpleEngine::Instance()->GetScene()->GetLowerZIndex() - 1);
	SimpleEngine::Instance()->GetScene()->AddLayer(layer);
	
	/*SimpleDebugObject* obj = new SimpleDebugObject();
	SimpleEngine::Instance()->GetScene()->AddEntity(obj, layer);*/

	SimpleSpriteRenderer * sprite = new SimpleSpriteRenderer();
	sprite->SetAsTexture("./media/spriteFullPOT.png");
	//sprite->GetTexture()->SetPixelated();
	SimpleEngine::Instance()->GetScene()->AddEntity(sprite, layer);

	
	layer = new SimpleLayer();
	layer->SetZ(SimpleEngine::Instance()->GetScene()->GetLowerZIndex() - 1);
	SimpleEngine::Instance()->GetScene()->AddLayer(layer);
	sprite = new SimpleSpriteRenderer();
	sprite->SetAsTexture("./media/spriteSheet.png");
	SimpleEngine::Instance()->GetScene()->AddEntity(sprite, layer);


	layer = new SimpleLayer();
	layer->SetZ(SimpleEngine::Instance()->GetScene()->GetLowerZIndex() - 1);
	SimpleEngine::Instance()->GetScene()->AddLayer(layer);
	sprite = new SimpleSpriteRenderer();
	sprite->SetAsTexture("./media/spriteFull.png");
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
