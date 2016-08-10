#include "stdafx.h"
#include "SpriteControl.h"
#include "SimpleEngine.h"

using namespace System::Runtime::InteropServices;

using namespace SimpleEngineControls;

SpriteControl::SpriteControl() {
	_simpleLayer = new SimpleLayer();
	_simpleSpriteRenderer = new SimpleSpriteRenderer();
	_managedSimpleObject = gcnew ManagedSimpleObject();
	_managedSimpleObject->SetSimpleObject(_simpleSpriteRenderer);
}

SpriteControl::~SpriteControl() {
	//free(_simpleSpriteRenderer); This won't call the destructor, its the c way
	delete _simpleSpriteRenderer;
}

void SpriteControl::AddControl(System::String^ path)// , glm::vec3 _position, glm::vec2 _size) 
{
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(path)).ToPointer();

	_simpleSpriteRenderer->SetAsTexture(chars);
	
	//For now all the images go to the default layer (0)
	SimpleEngine::Instance()->GetScene()->AddEntity(_simpleSpriteRenderer, 0);
}

ManagedSimpleObject^ SpriteControl::GetManagedSimpleObject() {
	return this->_managedSimpleObject;
}