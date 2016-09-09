#pragma once
#include "SimpleConfiguration.h"
#include "SimpleWindow.h"

class SIMPLE_API DebugSimpleWindow : public SimpleWindow {

	virtual void Initialize();
	virtual void Shutdown() {
	
	};

	virtual const char* GetFilename() { return "TestUI.layout"; }
	
};