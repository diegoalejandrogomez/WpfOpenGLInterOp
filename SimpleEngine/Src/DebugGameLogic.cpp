#include "stdafx.h"
#include "DebugGameLogic.h"
#include "SimpleDebugObject.h"
#include "SimpleEngine.h"
#include "SimpleLayer.h"
#include "SimpleSpriteRenderer.h"
#include "SimpleSpriteSheetRenderer.h"
#include "SimpleAnimatedSpriteRenderer.h"

void DebugGameLogic::Init()
{

	SimpleLayer* layer = new SimpleLayer();
	layer->SetZ(SimpleEngine::Instance()->GetScene()->GetLowerZIndex() - 1);
	SimpleEngine::Instance()->GetScene()->AddLayer(layer);
	
	layer = new SimpleLayer();
	layer->SetZ(SimpleEngine::Instance()->GetScene()->GetLowerZIndex() - 1);
	SimpleEngine::Instance()->GetScene()->AddLayer(layer);
	
	/*SimpleSpriteRenderer* sprite = new SimpleSpriteRenderer();
	sprite->SetAsTexture("./media/spriteFull.png");
	sprite->SetOrientation(1.0f);*/
	//SimpleEngine::Instance()->GetScene()->AddEntity(sprite, layer);
	
	SimpleEngine::Instance()->GetRenderer()->CreateSpriteSheet("media/spriteSheet.png", { 104,149 }, { 6,3 });

	
	/*
	SimpleSpriteSheetRenderer* guybrush = new SimpleSpriteSheetRenderer();
	guybrush->SetSpriteSheet("media/spriteSheet.png");
	guybrush->SetIndex(1, 0);*/
	//SimpleEngine::Instance()->GetScene()->AddEntity(guybrush, layer);
	
	//Guybrush animation
	SimpleEngine::Instance()->GetRenderer()->CreateSpriteAnimation(	"walking","media/spriteSheet.png",
		std::vector<SimpleSpriteAnimation::AnimationIndex>{ {0, 0}, { 1,0 }, { 2,0 }, { 3,0 }, { 4,0 }, { 5,0 } }, 0.15f);
		
	SimpleSpriteAnimation *walkingAnim = SimpleEngine::Instance()->GetRenderer()->GetSpriteAnimation("walking");
	
	SimpleAnimatedSpriteRenderer* walkingGuybrush = new SimpleAnimatedSpriteRenderer();
	walkingGuybrush->SetAnimation(walkingAnim);
	walkingGuybrush->Play();
	SimpleEngine::Instance()->GetScene()->AddEntity(walkingGuybrush, layer);


	//Configure input system we are going to use
	SimpleEngine::Instance()->GetInput()->CreateKeyboard();
	SimpleEngine::Instance()->GetInput()->CreateMouse();
	
}

void DebugGameLogic::Advance(float dt)
{
	auto keyboard = SimpleEngine::Instance()->GetInput()->GetKeyboard();
	auto mouse = SimpleEngine::Instance()->GetInput()->GetMouse();
	auto camera = SimpleEngine::Instance()->GetScene()->GetCamera();
	auto scene = SimpleEngine::Instance()->GetScene();

	if (keyboard->isKeyDown(OIS::KeyCode::KC_UP))
		camera->Move(0.0, 1.0f);
	if (keyboard->isKeyDown(OIS::KeyCode::KC_DOWN))
		camera->Move(0.0, -1.0f);
	if (keyboard->isKeyDown(OIS::KeyCode::KC_LEFT))
		camera->Move(-1.0, 0.0f);
	if (keyboard->isKeyDown(OIS::KeyCode::KC_RIGHT))
		camera->Move(1.0, 0.0f);
	
	
	auto state = mouse->getMouseState();
	glm::vec2 worldPos = camera->ScreenToWorld({ state.X.abs, state.Y.abs });
	
	//SIMPLE_LOG("Mouse at (%.2f,%.2f)", worldPos.x, worldPos.y);
	if (state.buttonDown(OIS::MouseButtonID::MB_Left)) {
		glm::vec2 worldPos = camera->ScreenToWorld({ state.X.abs, state.Y.abs });
		SimpleObject* res = scene->PickFirst({ (float)worldPos.x, worldPos.y });
		SimpleSpriteRenderer *sprite = dynamic_cast<SimpleSpriteRenderer*>(res);
		if (sprite != nullptr) {	
			SIMPLE_LOG("Found sprite at (%.2f,%.2f)", worldPos.x, worldPos.y);
		}
	}
}

void DebugGameLogic::Shutdown()
{
	SimpleEngine::Instance()->GetInput()->DestroyKeyboard();
}

bool DebugGameLogic::IsRunning()
{
	return true;
}
