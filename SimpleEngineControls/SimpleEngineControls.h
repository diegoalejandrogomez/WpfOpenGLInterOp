// SimpleEngineControls.h

#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace SimpleEngineControls {
	
	static bool IsInDesignMode()
	{
		if (System::Reflection::Assembly::GetExecutingAssembly()->Location->Contains("VisualStudio"))
		{
			return true;
		}
		return false;
	}
	
}
