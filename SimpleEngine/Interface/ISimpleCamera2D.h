#pragma once
#include "SimpleCamera2D.h"

extern "C" {
	
	SIMPLE_API void SimpleCamera2D_SetPosition(float x, float y);

	SIMPLE_API void SimpleCamera2D_SetZoom(float zoom);

	SIMPLE_API void SimpleCamera2D_SetMaxVisibleArea(float x, float y, float width, float height);

	SIMPLE_API void SimpleCamera2D_Move(float dx, float dy);

	SIMPLE_API void SimpleCamera2D_DeltaZoom(float dz);

	SIMPLE_API void SimpleCamera2D_ZoomToArea(float x, float y, float width, float height);

	SIMPLE_API void SimpleCamera2D_SetViewportSize(float w, float h);

	SIMPLE_API float SimpleCamera2D_GetWidth();
	
	SIMPLE_API float SimpleCamera2D_GetHeight();
	
	SIMPLE_API float SimpleCamera2D_GetZoom();
	
	SIMPLE_API float SimpleCamera2D_GetMaxZoom();

	SIMPLE_API void SimpleCamera2D_ScreenToWorld(int& x, int& y);
	
	SIMPLE_API void SimpleCamera2D_ViewportToWorld(int& x, int& y);

	SIMPLE_API void SimpleCamera2D_WorldToScreen(int& x, int& y);
	
	SIMPLE_API void SimpleCamera2D_WorldToViewport(int& x, int& y);
}
