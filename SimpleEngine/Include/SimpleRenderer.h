#pragma once
#include "stdafx.h"
#include "RenderPass.h"
#include <vector>

class SimpleRenderer {

public:
	SimpleRenderer();
	virtual ~SimpleRenderer();
	
	bool InitializeOpenGL(HWND hWnd, int width, int height);
	void AddPass(RenderPass *p) { _passes.push_back(p); }
	void Render();

private:

	bool _InitializeExtensions();

	//Opengl fields
	HDC _deviceContext;
	HGLRC _renderingContext;

	std::vector<RenderPass*> _passes;

};