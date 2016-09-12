#pragma once
#include "SimpleConfiguration.h"
#include "SimpleWindow.h"
#include "DebugSimplePopup.h"

class SIMPLE_API DebugSimpleWindow : public SimpleWindow {

public:

	virtual void Initialize();
	virtual void Shutdown() {
	
	};

	void OnOpenWindowButton(MyGUI::Widget* w);
	void OnCloseWindowButton(MyGUI::Widget* w);
	void OnSendButton(MyGUI::Widget* w);

	virtual const char* GetFilename() { return "TestUI.layout"; }
	
private:

	DebugSimplePopup* _popup;
	
};