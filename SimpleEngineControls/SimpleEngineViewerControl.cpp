#include "Stdafx.h"
#include "SimpleEngineViewerControl.h"
#include <SimpleEngine.h>

using namespace SimpleEngineControls;

void SimpleEngineViewerControl::OnLoad(System::Object ^sender, System::EventArgs ^e){
	HWND  _hWnd= (HWND) this->Handle.ToPointer();

	SimpleEngine* eng = SimpleEngine::Instance();
	eng->InitRenderer(_hWnd, Width, Height);
}


void SimpleEngineViewerControl::OnSizeChanged(System::Object ^sender, System::EventArgs ^e){
	
}


void SimpleEngineViewerControl::OnPaintBackground(PaintEventArgs^ e)  {


}
void SimpleEngineViewerControl::OnPaint(PaintEventArgs^ e)  {

}