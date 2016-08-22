// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SIMPLEENGINENATIVETILEEDITOR_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SIMPLEENGINENATIVETILEEDITOR_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TILEEDITOR_EXPORTS
#define TILEEDITOR_API __declspec(dllexport)
#else
#define TILEEDITOR_API __declspec(dllimport)
#endif

//// This class is exported from the SimpleEngineNativeTileEditor.dll
//class SIMPLEENGINENATIVETILEEDITOR_API CSimpleEngineNativeTileEditor {
//public:
//	CSimpleEngineNativeTileEditor(void);
//	// TODO: add your methods here.
//};
//
//extern SIMPLEENGINENATIVETILEEDITOR_API int nSimpleEngineNativeTileEditor;
//
//SIMPLEENGINENATIVETILEEDITOR_API int fnSimpleEngineNativeTileEditor(void);
