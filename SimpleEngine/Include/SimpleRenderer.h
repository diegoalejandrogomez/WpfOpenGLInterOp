#pragma once
#include "stdafx.h"
#include "RenderPass.h"
#include <vector>
#include <unordered_map>
#include <GL\GL.h>
#include "SimpleShaderProgram.h"
#include "SimpleMesh.h"
#include "SimpleTexture.h"
#include "VertexFormats.h"
#include "SimpleSpriteSheet.h"
#include "SimpleSpriteAnimation.h"
#include "SimpleID.h"
#include "SimpleConfiguration.h"
#include "SimpleTexture.h"
#include "SimpleColor.h"
#include "SimpleTextRenderer.h"

class SimpleScene;

class SIMPLE_API SimpleRenderer {
public:




	SimpleRenderer();
	virtual ~SimpleRenderer();
	
	bool InitializeOpenGL(HWND hWnd, int width, int height);
	void AddPass(RenderPass *p) { _passes.push_back(p); }
	void Initialize();
	void Shutdown();
	void Render(float dt, SimpleScene* scene);
	void ResizeWindow(int width, int height);
	void SetClearColor(SimpleColor c) { _clearColor = c; }
	void ShowDebugInfo();
	inline int GetWidth()const { return _width; } ;
	inline int GetHeight()const { return _height; } ;

	inline SimpleMesh<VertexTextureFormat2D>* GetUnitaryQuad() { return _texturedQuad; };
	inline HWND GetWindowHandle() { return _hWnd; };

	void ClearPasses();

	
private:

	bool _InitializeExtensions();
	
	bool _LoadDefaultShaders();
	
	//Window parameters (Target render surface)
	int _width;
	int _height;

	//Opengl fields
	HDC _deviceContext;
	HGLRC _renderingContext;

	//Window handle caching
	HWND _hWnd;

	//Default render buffer
	GLint _defaultRenderBuffer;
	
	//Render passes
	std::vector<RenderPass*> _passes;

	//Clear color
	SimpleColor _clearColor;

	//Reusable meshes
	SimpleMesh<VertexTextureFormat2D>* _texturedQuad;

	
	
		

};
