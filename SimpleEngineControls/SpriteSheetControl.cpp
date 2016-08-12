#include "stdafx.h"
#include "SpriteSheetControl.h"
#include "SimpleEngine.h"
#include "TileEditorApp.h"

using namespace System::Runtime::InteropServices;

using namespace SimpleEngineControls;

SpriteSheetControl::SpriteSheetControl() {
	_simpleSpriteSheetRenderer = new SimpleSpriteSheetRenderer();
	_managedSimpleObject = gcnew ManagedSimpleObject();
	//_managedSimpleObject->SetSimpleObject(_simpleSpriteRenderer);
}

SpriteSheetControl::~SpriteSheetControl() {
	delete _simpleSpriteSheetRenderer;
}

void SpriteSheetControl::AddControl(System::String^ path, int x, int y, int w, int h)
{
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(path)).ToPointer();

	SimpleSpriteSheet* sheet = SimpleEngine::Instance()->GetRenderer()->GetSpriteSheet(chars);
	if (sheet == nullptr) {
		SimpleEngine::Instance()->GetRenderer()->CreateSpriteSheet(chars);
		sheet = SimpleEngine::Instance()->GetRenderer()->GetSpriteSheet(chars);
	}

	int idx = sheet->GetFrameIndex({ x,y }, { w,h });
	if(idx == -1)
		idx = sheet->AddSpriteFrame({ x,y }, { w,h });


	//Set the brush instead of putting the tile in the world
	TileEditorApp* app = dynamic_cast<TileEditorApp*>(SimpleEngine::Instance()->GetGameLogic());
	app->SetCursorTile(chars, idx);
	/*_simpleSpriteSheetRenderer->SetSpriteSheet(chars);
	_simpleSpriteSheetRenderer->SetIndex(idx);
	_simpleSpriteSheetRenderer->SetSize({ 1, 1 });
	_simpleSpriteSheetRenderer->SnapToGrid(true);
	_simpleSpriteSheetRenderer->SetSnapGridSize({ 1, 1 });
	_simpleSpriteSheetRenderer->SetPosition({ 0.0f,0.0f,0.0f });
	
	SimpleEngine::Instance()->GetScene()->AddEntity(_simpleSpriteSheetRenderer, "MainTileMap");*/
}

ManagedSimpleObject^ SpriteSheetControl::GetManagedSimpleObject() {
	return this->_managedSimpleObject;
}
