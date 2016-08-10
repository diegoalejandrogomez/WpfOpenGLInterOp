#include "Stdafx.h"
#include "SimpleEngineViewerControl.h"
#include <SimpleEngine.h>
#include <SimpleRenderer.h>
#include "ManagedSimpleObject.h"
using namespace SimpleEngineControls;



SimpleEngineViewerControl::SimpleEngineViewerControl() {
	this->Load += gcnew System::EventHandler(this, &SimpleEngineViewerControl::OnLoad);
	this->SizeChanged += gcnew System::EventHandler(this, &SimpleEngineViewerControl::OnSizeChanged);
}


void SimpleEngineViewerControl::OnLoad(System::Object ^sender, System::EventArgs ^e){
	
}	

void SimpleEngineViewerControl::Initialize() {

	HWND  _hWnd = (HWND) this->Handle.ToPointer();
	SimpleEngine* eng = SimpleEngine::Instance();
	eng->InitRenderer(_hWnd, Width, Height);
	eng->InitInput((HWND)WPFWindowHandle.ToPointer(), false);
	eng->Initialize();

	_appLogic = new TileEditorApp();
	SimpleEngine::Instance()->SetGameLogic(_appLogic);

}

void SimpleEngineViewerControl::OnSizeChanged(System::Object ^sender, System::EventArgs ^e){
	
	SimpleEngine* eng = SimpleEngine::Instance();
	SimpleRenderer* render = eng->GetRenderer();
	if (render != nullptr)
		render->ResizeWindow(Width, Height);

	//System::Diagnostics::Debug::WriteLine("OnSizeChanged");
}


void SimpleEngineViewerControl::OnPaintBackground(PaintEventArgs^ e)  {

}

void SimpleEngineViewerControl::OnPaint(PaintEventArgs^ e)  {
	
	SimpleEngine::Instance()->Advance(0.0f);
	SimpleEngine::Instance()->Render(0.0f);
	//System::Diagnostics::Debug::WriteLine("OnPaint");

}

ManagedSimpleObject^ SimpleEngineViewerControl::SetItem(float x, float y)
{
	glm::vec2 worldPos = SimpleEngine::Instance()->GetScene()->GetCamera()->ScreenToWorld({ x, y });

	SimpleObject* res = SimpleEngine::Instance()->GetScene()->PickFirst({ (float)worldPos.x, worldPos.y });
	SimpleObject *sprite = dynamic_cast<SimpleObject*>(res);
	if (sprite != nullptr) {
		ManagedSimpleObject^ SelectedObject = gcnew ManagedSimpleObject();
		SelectedObject->SetSimpleObject(sprite);
		return SelectedObject;
	}

	return nullptr;
}

