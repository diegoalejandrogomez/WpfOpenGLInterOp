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
	virtual void Shutdown() = 0 ;
	void Load();
	void Unload();
	virtual const char* GetFilename() { return ""; }
protected:
	MyGUI::Gui* _gui;
	MyGUI::VectorWidgetPtr _controls;

};