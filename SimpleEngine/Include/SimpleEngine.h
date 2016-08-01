#pragma once
#include "SimpleRenderer.h"
#include "SimpleScene.h"

class SimpleEngine final{

	SimpleRenderer * _renderer = nullptr;
	SimpleScene* _scene = nullptr;
public:

	SimpleEngine();
	~SimpleEngine();
	
	void InitRenderer(HWND hWnd, uint32_t width, uint32_t height);

	void Render(float dt);
	void Advance(float dt);
		
};