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

	SimpleEngine::Instance()->GetRenderer()->CreateSpriteSheet(chars, { width, heigth }, { positionX, positionY });
	_simpleSpriteSheetRenderer->SetSpriteSheet(chars);
	_simpleSpriteSheetRenderer->SetIndex(0);
}

ManagedSimpleObject^ SpriteSheetControl::GetManagedSimpleObject() {
	return this->_managedSimpleObject;
}
