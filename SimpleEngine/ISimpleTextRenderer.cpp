#include "stdafx.h"
#include "ISimpleTextRenderer.h"

extern "C" {
	SIMPLE_API SimpleTextRenderer* SimpleTextRenderer_Create()
	{
		return new SimpleTextRenderer();
	}

	SIMPLE_API void SimpleTextRenderer_Destroy(SimpleTextRenderer* simpleTextRenderer)
	{
		delete simpleTextRenderer;
	}

	SIMPLE_API void SimpleTextRenderer_SetText(SimpleTextRenderer* simpleTextRenderer, const char* text)
	{
		simpleTextRenderer->SetText(text);
	}

	SIMPLE_API void SimpleTextRenderer_SetFontName(SimpleTextRenderer* simpleTextRenderer, const char* name)
	{
		simpleTextRenderer->SetFontName(name); //implement with rvalue
	}

	SIMPLE_API void SimpleTextRenderer_SetFontSize(SimpleTextRenderer* simpleTextRenderer, float size)
	{
		simpleTextRenderer->SetFontSize(size);
	}

	SIMPLE_API void SimpleTextRenderer_SetColor(SimpleTextRenderer* simpleTextRenderer, int r, int g, int b, int a)
	{
		simpleTextRenderer->SetColor({(uint32_t)r, (uint32_t)g, (uint32_t)b, (uint32_t)a});
	}

	SIMPLE_API const char* SimpleTextRenderer_GetText(SimpleTextRenderer* simpleTextRenderer)
	{
		return simpleTextRenderer->GetText().c_str();;
	}

	SIMPLE_API const char* SimpleTextRenderer_GetFontName(SimpleTextRenderer* simpleTextRenderer)
	{
		return simpleTextRenderer->GetFontName().c_str();;
	}

	SIMPLE_API float SimpleTextRenderer_GetFontSize(SimpleTextRenderer* simpleTextRenderer)
	{
		return simpleTextRenderer->GetFontSize();
	}

	SIMPLE_API SimpleColor SimpleTextRenderer_GetColor(SimpleTextRenderer* simpleTextRenderer)
	{
		return simpleTextRenderer->GetColor();
	}
}