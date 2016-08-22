// SimpleEngineNativeTileEditor.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SimpleEngineNativeTileEditor.h"


// This is an example of an exported variable
SIMPLEENGINENATIVETILEEDITOR_API int nSimpleEngineNativeTileEditor=0;

// This is an example of an exported function.
SIMPLEENGINENATIVETILEEDITOR_API int fnSimpleEngineNativeTileEditor(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see SimpleEngineNativeTileEditor.h for the class definition
CSimpleEngineNativeTileEditor::CSimpleEngineNativeTileEditor()
{
    return;
}
