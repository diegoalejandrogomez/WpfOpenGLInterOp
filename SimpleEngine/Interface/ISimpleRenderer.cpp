#include "stdafx.h"
#include "SimpleRenderer.h"
#include "SimpleConfiguration.h"
#include "SimpleEngine.h"

extern "C" {
	SIMPLE_API void SimpleRenderer_ResizeWindow(int width, int height) {
		SimpleEngine::Instance()->GetRenderer()->ResizeWindow(width, height);
	}

	SIMPLE_API int SimpleRenderer_GetWidth() {
		return SimpleEngine::Instance()->GetRenderer()->GetWidth();
	};

	SIMPLE_API int SimpleRenderer_GetHeight() {
		return SimpleEngine::Instance()->GetRenderer()->GetHeight();
	};


}