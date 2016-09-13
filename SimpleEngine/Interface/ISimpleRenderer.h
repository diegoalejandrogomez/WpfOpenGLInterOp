#pragma once
#include "SimpleConfiguration.h"

extern "C" {

	SIMPLE_API void SimpleRenderer_ResizeWindow(int width, int height);

	SIMPLE_API int SimpleRenderer_GetWidth();

	SIMPLE_API int SimpleRenderer_GetHeight();

}