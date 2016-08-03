#include "Stdafx.h"
#include "SimpleEngineViewerControl.h"
#include <SimpleEngine.h>
#include <SimpleRenderer.h>

using namespace SimpleEngineControls;

void SimpleEngineViewerControl::OnLoad(System::Object ^sender, System::EventArgs ^e){
	HWND  _hWnd= (HWND) this->Handle.ToPointer();

	SimpleEngine* eng = SimpleEngine::Instance();
	eng->InitRenderer(_hWnd, Width, Height);
}


void SimpleEngineViewerControl::OnSizeChanged(System::Object ^sender, System::EventArgs ^e){
	
	SimpleEngine* eng = SimpleEngine::Instance();
	SimpleRenderer* render = eng->GetRenderer();
	if (render != nullptr)
		render->ResizeWindow(Width, Height);
}


void SimpleEngineViewerControl::OnPaintBackground(PaintEventArgs^ e)  {


}
void SimpleEngineViewerControl::OnPaint(PaintEventArgs^ e)  {

	SimpleEngine::Instance()->Advance(0.0f);
	SimpleEngine::Instance()->Render(0.0f);

}