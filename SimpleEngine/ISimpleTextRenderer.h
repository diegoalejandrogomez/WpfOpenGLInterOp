#pragma once
#include "SimpleTextRenderer.h"
#include "SimpleConfiguration.h"

extern "C" {

	SIMPLE_API SimpleTextRenderer* SimpleTextRenderer_Create();
	SIMPLE_API void SimpleTextRenderer_Destroy(SimpleTextRenderer* simpleTextRenderer);

	SIMPLE_API void SimpleTextRenderer_SetText(SimpleTextRenderer* simpleTextRenderer, const char* text);
	SIMPLE_API void SimpleTextRenderer_SetFontName(SimpleTextRenderer* simpleTextRenderer, const char* name);
	SIMPLE_API void SimpleTextRenderer_SetFontSize(SimpleTextRenderer* simpleTextRenderer, float size);
	SIMPLE_API void SimpleTextRenderer_SetColor(SimpleTextRenderer* simpleTextRenderer, int r, int g, int b, int a);

	SIMPLE_API const char* SimpleTextRenderer_GetText(SimpleTextRenderer* simpleTextRenderer);
	SIMPLE_API const char* SimpleTextRenderer_GetFontName(SimpleTextRenderer* simpleTextRenderer);
	SIMPLE_API float SimpleTextRenderer_GetFontSize(SimpleTextRenderer* simpleTextRenderer);
	SIMPLE_API SimpleColor SimpleTextRenderer_GetColor(SimpleTextRenderer* simpleTextRenderer);
}

