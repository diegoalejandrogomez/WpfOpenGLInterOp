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

	inline int GetWidth()const { return _width; } ;
	inline int GetHeight()const { return _height; } ;

	bool CreateProgram(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
	SimpleShaderProgram* GetProgram(SimpleID name) const;
	
	bool LoadTexture(std::string texturePath);
	SimpleTexture* GetTexture(SimpleID name) ;
	
	bool CreateSpriteSheet(std::string texturePath, glm::ivec2 frameSize, glm::ivec2 frameCount);
	bool CreateSpriteSheet(std::string texturePath);
	SimpleSpriteSheet* GetSpriteSheet(SimpleID texturePath);

	bool CreateSpriteAnimation(std::string name, std::string spriteSheet, std::vector<int> &frames, float frameTime);
	bool CreateSpriteAnimation(std::string name);

	SimpleSpriteAnimation* GetSpriteAnimation(SimpleID name);

	inline SimpleMesh<VertexTextureFormat2D>* GetUnitaryQuad() { return _texturedQuad; };
	inline HWND GetWindowHandle() { return _hWnd; };

	bool SerializeResources(std::string dir);
	bool DeserializeResources(std::string dir);
	
	void ClearResources();
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

	//This class also serves as a mini graphics resource admin
	//Memory owners
	std::unordered_map<SimpleID, SimpleShaderProgram*> _programs;
	std::unordered_map<SimpleID, SimpleTexture*> _textures;
	std::unordered_map<SimpleID, SimpleSpriteSheet*> _spriteSheets;
	//Don't own anything
	std::unordered_map<SimpleID, SimpleSpriteAnimation*> _spriteAnimations;

	//Reusable meshes
	SimpleMesh<VertexTextureFormat2D>* _texturedQuad;
	

};
