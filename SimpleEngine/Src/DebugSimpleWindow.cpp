#include "stdafx.h"
#include "DebugSimpleWindow.h"
#include "MyGUI_Gui.h"
#include "MyGUI.h"
#include "SimpleGUI.h"
#include "DebugSimplePopup.h"


 void DebugSimpleWindow::Initialize(){

 MyGUI::ButtonPtr button = _gui->findWidget<MyGUI::Button>("exitButton");
 auto exitLambda = [](MyGUI::Widget* w) { PostQuitMessage(0);};
 // set callback
 button->eventMouseButtonClick += MyGUI::newDelegate<MyGUI::Widget*>(exitLambda);

 button = _gui->findWidget<MyGUI::Button>("openButton");
 button->eventMouseButtonClick += MyGUI::newDelegate<DebugSimpleWindow>(this, &DebugSimpleWindow::OnOpenWindowButton);

 button = _gui->findWidget<MyGUI::Button>("closeButton");
 button->eventMouseButtonClick += MyGUI::newDelegate<DebugSimpleWindow>(this, &DebugSimpleWindow::OnCloseWindowButton);

 button = _gui->findWidget<MyGUI::Button>("sendButton");
 button->eventMouseButtonClick += MyGUI::newDelegate<DebugSimpleWindow>(this, &DebugSimpleWindow::OnSendButton);

}


 
 void DebugSimpleWindow::OnOpenWindowButton(MyGUI::Widget* w) {
 
	 _popup = new DebugSimplePopup();
	 SimpleEngine::Instance()->GetGUI()->PushWindow(_popup);
 
 }

 void DebugSimpleWindow::OnCloseWindowButton(MyGUI::Widget* w) {
	 if (_popup != nullptr)
		 _popup->Close();
	 _popup = nullptr;
 }


 void DebugSimpleWindow::OnSendButton(MyGUI::Widget* w) {
	
	 MyGUI::ListBox* _lbox = _gui->findWidget<MyGUI::ListBox>("statusListBox");
	 MyGUI::EditBox* _editBox = _gui->findWidget<MyGUI::EditBox>("sendEditBox");

	 _lbox->addItem(_editBox->getCaption() );
	 _editBox->setCaption("");
	 
 }


