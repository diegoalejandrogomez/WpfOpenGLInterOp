#include "stdafx.h"
#include "DebugSimpleWindow.h"
#include "MyGUI_Gui.h"
#include "MyGUI.h"

 void DebugSimpleWindow::Initialize(){

 MyGUI::ButtonPtr button = _gui->findWidget<MyGUI::Button>("ExitButton");
 auto lambda = [](MyGUI::Widget* w) { PostQuitMessage(0);};

 // set callback
 button->eventMouseButtonClick += MyGUI::newDelegate<MyGUI::Widget*>(lambda);


}