#include "stdafx.h"
#include "SimpleWindow.h"
#include "MyGUI.h"
#include "MyGUI_Gui.h"


SimpleWindow::~SimpleWindow() {
	Unload();
}
SimpleWindow::SimpleWindow() {
		
}

void SimpleWindow::Load() {

	_gui = MyGUI::Gui::getInstancePtr();
	_controls = MyGUI::LayoutManager::getInstance().loadLayout(GetFilename());

}
void SimpleWindow::Unload() {

	MyGUI::LayoutManager::getInstance().unloadLayout(_controls);

}

