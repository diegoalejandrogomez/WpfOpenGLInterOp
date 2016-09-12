#pragma once
#include "SimpleConfiguration.h"
#include "SimpleEngine.h"
#include <vector>
namespace MyGUI {
	class Gui;
	class Widget;
	typedef std::vector<Widget*> VectorWidgetPtr;
};
class SIMPLE_API SimpleWindow {

public:

	SimpleWindow();
	~SimpleWindow();
	virtual void Initialize() = 0; //Use to hook to events
	virtual void Shutdown() = 0 ; //Use this to release events
	void Load();
	void Unload();
	void Close();
	MyGUI::Widget* GetRootControl();
	virtual const char* GetFilename() { return ""; }
	virtual const bool IsModal() { return false; }
protected:
	MyGUI::Gui* _gui;
	MyGUI::VectorWidgetPtr _controls;

};