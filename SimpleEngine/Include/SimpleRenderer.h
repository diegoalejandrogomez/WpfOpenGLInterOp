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


class SimpleScene;

class SimpleRenderer {

public:
	SimpleRenderer();
	virtual ~SimpleRenderer();
	
	bool InitializeOpenGL(HWND hWnd, int width, int height);
	void AddPass(RenderPass *p) { _passes.push_back(p); }
	void Render(float dt, SimpleScene* scene);
	void ResizeWindow(int width, int height);

	inline int GetWidth()const { return _width; } ;
	inline int GetHeight()const { return _height; } ;

	bool CreateProgram(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
	SimpleShaderProgram* GetProgram(std::string name) const;
	
	bool LoadTexture(std::string texturePath);
	SimpleTexture* GetTexture(std::string name) ;

	inline SimpleMesh<VertexTextureFormat2D>* GetUnitaryQuad() { return _texturedQuad; };
	inline HWND GetWindowHandle() { return _hWnd; };
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

	//This class also serves as a mini graphics resource admin
	std::unordered_map<std::string, SimpleShaderProgram*> _programs;
	std::unordered_map<std::string, SimpleTexture*> _textures;

	//Reusable meshes
	SimpleMesh<VertexTextureFormat2D>* _texturedQuad;
	

};