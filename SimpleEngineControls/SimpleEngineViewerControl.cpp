#include "Stdafx.h"
#include "SimpleEngineViewerControl.h"
#include <SimpleEngine.h>
#include <SimpleRenderer.h>

using namespace SimpleEngineControls;



SimpleEngineViewerControl::SimpleEngineViewerControl() {
	this->Load += gcnew System::EventHandler(this, &SimpleEngineViewerControl::OnLoad);
	this->SizeChanged += gcnew System::EventHandler(this, &SimpleEngineViewerControl::OnSizeChanged);
	/*_appLogic = new DrawingAppLogic();
	SimpleEngine::Instance()->SetGameLogic(_appLogic);*/

}


void SimpleEngineViewerControl::OnLoad(System::Object ^sender, System::EventArgs ^e){
	HWND  _hWnd= (HWND) this->Handle.ToPointer();

	SimpleEngine* eng = SimpleEngine::Instance();
	eng->InitRenderer(_hWnd, Width, Height);
	eng->Initialize();
}	


void SimpleEngineViewerControl::OnSizeChanged(System::Object ^sender, System::EventArgs ^e){
	
	SimpleEngine* eng = SimpleEngine::Instance();
	SimpleRenderer* render = eng->GetRenderer();
	if (render != nullptr)
		render->ResizeWindow(Width, Height);

	System::Diagnostics::Debug::WriteLine("OnSizeChanged");
}


void SimpleEngineViewerControl::OnPaintBackground(PaintEventArgs^ e)  {

}
void SimpleEngineViewerControl::OnPaint(PaintEventArgs^ e)  {

	SimpleEngine::Instance()->Advance(0.0f);
	SimpleEngine::Instance()->Render(0.0f);
	System::Diagnostics::Debug::WriteLine("OnPaint");

}