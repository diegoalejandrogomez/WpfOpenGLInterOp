#pragma once
#include "SimpleRenderer.h"

class SimpleEngine final{

	SimpleRenderer * _renderer = nullptr;

public:

	SimpleEngine();
	~SimpleEngine();
	
	void InitRenderer(HWND hWnd, uint32_t width, uint32_t height);

	void Render(float dt);
	void Advance(float dt);
		
};