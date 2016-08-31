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

	//Font library
	struct SimpleCharacter {
		SimpleTexture* Texture;  //The glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		long  Advance;    // Offset to advance to next glyph
	};
	using FontCharacters = std::vector<SimpleCharacter>;


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

	bool LoadFont(std::string fontName, uint32_t size = 48);
	bool HasFont(SimpleID fontName);
	FontCharacters GetFontChars(SimpleID fontName);
	float GetFontScale(SimpleID fontName);
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

	//Clear color
	SimpleColor _clearColor;

	//This class also serves as a mini graphics resource admin
	//Memory owners
	std::unordered_map<SimpleID, SimpleShaderProgram*> _programs;
	std::unordered_map<SimpleID, SimpleTexture*> _textures;
	std::unordered_map<SimpleID, SimpleSpriteSheet*> _spriteSheets;
	//Don't own anything
	std::unordered_map<SimpleID, SimpleSpriteAnimation*> _spriteAnimations;

	//Reusable meshes
	SimpleMesh<VertexTextureFormat2D>* _texturedQuad;

	
	std::unordered_map<SimpleID, std::pair<float,FontCharacters>> _fonts;
		

};
