#include "stdafx.h"
#include "SimpleWindow.h"
#include "MyGUI.h"
#include "MyGUI_Gui.h"
#include "SimpleGUI.h"
#include "SimpleDispatcher.h"

SimpleWindow::~SimpleWindow() {
	Unload();
}
SimpleWindow::SimpleWindow() {
		
}

void SimpleWindow::Close() {
	SimpleGUI* gui = SimpleEngine::Instance()->GetGUI();
	//We can only close ourselves if we are the topmost window
	if (this == gui->GetTopWindow()) { 
		gui->PopWindow();
	}

	SimpleDispatcher::Instance()->Send<WindowClosed>(this, this);
}
void SimpleWindow::Load() {

	_gui = MyGUI::Gui::getInstancePtr();
	_controls = MyGUI::LayoutManager::getInstance().loadLayout(GetFilename());

}
void SimpleWindow::Unload() {

	if (!_controls.empty()) {
		MyGUI::LayoutManager::getInstance().unloadLayout(_controls);
		_controls.clear();
	}
}


MyGUI::Widget* SimpleWindow::GetRootControl() {
	
	if (_controls.empty())
		return nullptr;

	return _controls[0];

}
