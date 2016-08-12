#include "stdafx.h"
#include "SpriteSheetControl.h"
#include "SimpleEngine.h"

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

void SpriteSheetControl::AddControl(System::String^ path)
{
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(path)).ToPointer();

	SimpleSpriteSheet* sheet = SimpleEngine::Instance()->GetRenderer()->GetSpriteSheet(chars);
	if (sheet == nullptr) {
		SimpleEngine::Instance()->GetRenderer()->CreateSpriteSheet(chars);
		sheet = SimpleEngine::Instance()->GetRenderer()->GetSpriteSheet(chars);
	}

	int idx = sheet->GetFrameIndex({ positionX,positionY }, { width,heigth });
	if(idx == -1)
		idx = sheet->AddSpriteFrame({ positionX,positionY }, { width,heigth });

	_simpleSpriteSheetRenderer->SetSpriteSheet(chars);
	_simpleSpriteSheetRenderer->SetIndex(idx);
	SimpleEngine::Instance()->GetScene()->AddEntity(_simpleSpriteSheetRenderer, "MainTileMap");
}

ManagedSimpleObject^ SpriteSheetControl::GetManagedSimpleObject() {
	return this->_managedSimpleObject;
}
