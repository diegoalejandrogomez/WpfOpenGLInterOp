#include "stdafx.h"
#include "DebugSimplePopup.h"
#include "MyGUI_Window.h"
void DebugSimplePopup::Initialize() {

	MyGUI::Window* wnd = dynamic_cast<MyGUI::Window*>(_controls[0]);
	wnd->eventWindowButtonPressed += MyGUI::newDelegate<DebugSimplePopup, MyGUI::Window*, const std::string&>(this, &DebugSimplePopup::OnClose);

	//MyGUI::ButtonPtr button = _gui->findWidget<MyGUI::Button>("exitButton");
	//auto exitLambda = [](MyGUI::Widget* w) { PostQuitMessage(0);};
	//// set callback
	//button->eventMouseButtonClick += MyGUI::newDelegate<MyGUI::Widget*>(exitLambda);

}

void DebugSimplePopup::OnClose(MyGUI::Window* sender, const std::string &name) {
	Close();
}

