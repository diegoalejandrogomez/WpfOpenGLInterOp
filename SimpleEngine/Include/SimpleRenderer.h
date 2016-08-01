#pragma once
#include "stdafx.h"
#include "RenderPass.h"
#include <vector>
#include <GL\GL.h>

class SimpleScene;

class SimpleRenderer {

public:
	SimpleRenderer();
	virtual ~SimpleRenderer();
	
	bool InitializeOpenGL(HWND hWnd, int width, int height);
	void AddPass(RenderPass *p) { _passes.push_back(p); }
	void Render(float dt, SimpleScene* scene);

private:

	bool _InitializeExtensions();

	//Opengl fields
	HDC _deviceContext;
	HGLRC _renderingContext;

	//Default render buffer
	GLint _defaultRenderBuffer;

	std::vector<RenderPass*> _passes;

};