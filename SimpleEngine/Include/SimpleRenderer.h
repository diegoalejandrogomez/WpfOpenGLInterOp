#pragma once
#include "stdafx.h"
#include "RenderPass.h"
#include <vector>
#include <unordered_map>
#include <GL\GL.h>
#include "SimpleShaderProgram.h"

class SimpleScene;

class SimpleRenderer {

public:
	SimpleRenderer();
	virtual ~SimpleRenderer();
	
	bool InitializeOpenGL(HWND hWnd, int width, int height);
	void AddPass(RenderPass *p) { _passes.push_back(p); }
	void Render(float dt, SimpleScene* scene);
	void ResizeWindow(int width, int height);

	int GetWidth() { return _width; };
	int GetHeight(){ return _height; };

	bool CreateProgram(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);

private:

	bool _InitializeExtensions();
	
	bool _LoadDefaultShaders();

	//Window parameters (Target render surface)
	int _width;
	int _height;

	//Opengl fields
	HDC _deviceContext;
	HGLRC _renderingContext;

	//Default render buffer
	GLint _defaultRenderBuffer;
	
	//Render passes
	std::vector<RenderPass*> _passes;

	//This class also serves as a mini graphics resource admin
	std::unordered_map<std::string, SimpleShaderProgram*> _programs;

};