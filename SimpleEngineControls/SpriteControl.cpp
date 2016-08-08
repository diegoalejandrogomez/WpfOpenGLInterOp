#include "stdafx.h"
#include "SpriteControl.h"
#include "SimpleEngine.h"

using namespace System::Runtime::InteropServices;

using namespace SimpleEngineControls;

SpriteControl::SpriteControl() {
	_simpleLayer = new SimpleLayer();
	_simpleSpriteRenderer = new SimpleSpriteRenderer();
	
}

SpriteControl::~SpriteControl() {
	free(_simpleSpriteRenderer);
}

void SpriteControl::AddControl(System::String^ path)// , glm::vec3 _position, glm::vec2 _size) 
{
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(path)).ToPointer();

	_simpleSpriteRenderer->SetAsTexture(chars);
	_simpleSpriteRenderer->SetSize(glm::vec2(500, 500));
	SimpleEngine::Instance()->GetScene()->AddLayer(_simpleLayer);
	
	SimpleEngine::Instance()->GetScene()->AddEntity(_simpleSpriteRenderer, _simpleLayer);
}
