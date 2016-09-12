#pragma once
#include "SimpleConfiguration.h"
#include "SimpleWindow.h"

namespace MyGUI {
	class Window;
}

class SIMPLE_API DebugSimplePopup : public SimpleWindow {

public:
	virtual void Initialize();
	virtual void Shutdown() {

	};
	

	void OnClose(MyGUI::Window* sender, const std::string &name);

	virtual const char* GetFilename() override{ return "TestPopup.layout"; }
	virtual const bool IsModal() override { return true; }

};