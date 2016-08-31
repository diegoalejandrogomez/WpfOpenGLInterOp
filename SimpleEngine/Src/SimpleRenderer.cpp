#include "stdafx.h"
#include "SimpleRenderer.h"
#include "SimpleScene.h"
#include "SimpleDispatcher.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <filesystem>
#include <fstream>
#include "SimpleEngine.h"
#include "SimpleObjectsRenderPass.h"
#include <ft2build.h>
#include FT_FREETYPE_H

//C++ 14/17 ... but why not XD
using namespace std::tr2::sys;

SimpleRenderer::SimpleRenderer() {
	_deviceContext = nullptr;
	_renderingContext = nullptr;
	_hWnd = 0;
	_clearColor = { 0,0,0,0 };
	_InitializeExtensions();
	
}

SimpleRenderer::~SimpleRenderer() {

	Shutdown();

	// Release the rendering context.
	if (_renderingContext)
	{
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(_renderingContext);
		_renderingContext = nullptr;
	}

	
};

void SimpleRenderer::Initialize() {
	_LoadDefaultShaders();
	//_renderer->AddPass(new DebugRenderPass());
	AddPass(new SimpleObjectsRenderPass());
}
void SimpleRenderer::Shutdown() {
	ClearResources();
	ClearPasses();
}

void SimpleRenderer::ClearPasses() {
	for (auto &pass : _passes)
		delete pass;
	_passes.clear();
}
void SimpleRenderer::ClearResources() {

	for (auto &shader : _programs)
		delete shader.second;
	_programs.clear();

	for (auto &tex : _textures)
		delete tex.second;
	_textures.clear();

	for (auto &sheet : _spriteSheets)
		delete sheet.second;
	_spriteSheets.clear();

	for (auto &animation : _spriteAnimations)
		delete animation.second;
	_spriteAnimations.clear();

}

void SimpleRenderer::Render(float dt, SimpleScene* scene ) {

	glViewport(0, 0, _width, _height);

	glClearColor(_clearColor.r / 255.0f, _clearColor.g / 255.0f, _clearColor.b / 255.0f, _clearColor.a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto &pass : _passes) {
		
		pass->Render(dt, scene);
	
	}

	SwapBuffers(_deviceContext);
}


bool SimpleRenderer::InitializeOpenGL(HWND hWnd, int width , int height) {
	
	_width = width;
	_height = height;
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	_hWnd = hWnd;
	_deviceContext = GetDC(hWnd);

	if (!_deviceContext) {
		SIMPLE_LOG("Couldn't obtain a device context");
		return false;
	}
	
	int  pixelFormat;

	pixelFormat = ChoosePixelFormat(_deviceContext, &pfd);
	if (!SetPixelFormat(_deviceContext, pixelFormat, &pfd)) {
		SIMPLE_LOG("Couldn't set pixel format");
		return false;
	}

	_renderingContext = wglCreateContext(_deviceContext);

	if (!_renderingContext) {
		SIMPLE_LOG("Couldn't create OpenGL context");
		return false;
	}

	
	if (!wglMakeCurrent(_deviceContext, _renderingContext)) {
	
		SIMPLE_LOG("Couldn't set the default context");
		return false;
	}


	SIMPLE_LOG("OPENGL VERSION: %s", (char*)glGetString(GL_VERSION));

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_defaultRenderBuffer);

	//Simple textured quad
	_texturedQuad = new SimpleMesh<VertexTextureFormat2D>();
	_texturedQuad->LoadQuad();

	//Initialized image library Devil
	ilInit();
	iluInit();

	return true;
}


LRESULT CALLBACK WndProcFake(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// Check if the window is being closed.
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:	
		return DefWindowProc(hWnd, message, wParam, lParam);
	
	}
}


bool SimpleRenderer::_InitializeExtensions() {
	
	WNDCLASSEX wc;

	
	
	// Get the instance of this application.
	HINSTANCE hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	LPCSTR applicationName = "Engine";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProcFake;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	if (!RegisterClassEx(&wc)) {
		SIMPLE_LOG(GetLastErrorAsString());
		return false;
	}

	// Create a temporary window for the OpenGL extension setup.
	HWND hwnd = CreateWindowEx(WS_EX_APPWINDOW, applicationName, applicationName, WS_POPUP,
		0, 0, 640, 480, NULL, NULL, hinstance, NULL);
	if (hwnd == NULL)
	{
		SIMPLE_LOG(GetLastErrorAsString());
		return false;
	}

	// Don't show the window.
	ShowWindow(hwnd, SW_HIDE);


	HDC deviceContext;
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error;
	HGLRC renderContext;
	
	// Get the device context for this window.
	deviceContext = GetDC(hwnd);
	if (!deviceContext)
	{
		SIMPLE_LOG("Couldn't get the device context");
		return false;
	}

	// Set a temporary default pixel format.
	error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if (error != 1)
	{
		SIMPLE_LOG("Couldn't set the pixel format");
		return false;
	}

	// Create a temporary rendering context.
	renderContext = wglCreateContext(deviceContext);
	if (!renderContext)
	{
		SIMPLE_LOG("Couldn't create a temporary render context");
		return false;
	}

	// Set the temporary rendering context as the current rendering context for this window.
	error = wglMakeCurrent(deviceContext, renderContext);
	if (error != 1)
	{
		SIMPLE_LOG("Couldn't set the active context");
		return false;
	}

	// Initialize the OpenGL extensions needed for this application.  Note that a temporary rendering context was needed to do so.
	
	error = glewInit();
	if (error != GLEW_OK)
	{
		SIMPLE_LOG("Couldn't load OpenGL extensions");
		return false;
	}
	
	// Release the temporary rendering context now that the extensions have been loaded.
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(renderContext);
	renderContext = nullptr;

	// Release the device context for this window.
	ReleaseDC(hwnd, deviceContext);
	deviceContext = 0;
	
	// Release the temporary window now that the extensions have been initialized.
	DestroyWindow(hwnd);
	hwnd = nullptr;


	return true;

}


void SimpleRenderer::ResizeWindow(int width, int height) {
	
	_width = width;
	_height = height;

	//Notify all listeners that the window has changed its size
	SimpleDispatcher::Instance()->Send<WindowResizeEvent>((float)_width, (float)_height);

}

bool SimpleRenderer::CreateProgram(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath) {
	
	//Don't reload if it already exists
	if (_programs.find(name) == _programs.end()) {
		SimpleShaderProgram* program = new SimpleShaderProgram();
		if (!program->CompileFromFile(vertexShaderPath, fragmentShaderPath)) {
			SIMPLE_LOG("Coulnd't compile shader %s",name );
			return false;
		}
		if (!program->Link()) {
			SIMPLE_LOG("Coulnd't link shader %s", name);
			return false;
		}
		_programs[name] = program;
	}

	return true;
}

SimpleShaderProgram* SimpleRenderer::GetProgram(SimpleID name) const {
	auto it = _programs.find(name);
	if(it== _programs.end())
		return nullptr;
	return it->second;
}


bool SimpleRenderer::LoadTexture(std::string texturePath) {
	
	if (_textures.find(texturePath) != _textures.end())
		return true; //Already loaded
	SimpleTexture* _tex = new SimpleTexture();
	_tex->LoadTexture(texturePath.c_str());
	_textures[texturePath] = _tex;
	return true;
}

SimpleTexture* SimpleRenderer::GetTexture(SimpleID texturePath) {

	auto tex = _textures.find(texturePath);
	if (tex == _textures.end()) 
		return nullptr;
	return tex->second;


}

//Equally spaced sprite sheet. Automatically creates the frames
bool SimpleRenderer::CreateSpriteSheet(std::string texturePath, glm::ivec2 frameSize, glm::ivec2 frameCount) {
	
	auto sheet = _spriteSheets.find(texturePath);
	if (sheet == _spriteSheets.end()) {
		//Try to load the texture
		SimpleSpriteSheet* spriteSheet = new SimpleSpriteSheet();	
		spriteSheet->LoadTexture(texturePath.c_str());
		spriteSheet->CreateUniformFrames(frameSize, frameCount);
		_spriteSheets[texturePath] = spriteSheet;
		
	}
	
	return true;
}

//Arbitrary sprite sheet. Must call AddSpriteFrame to set them
bool SimpleRenderer::CreateSpriteSheet(std::string texturePath) {

	auto sheet = _spriteSheets.find(texturePath);
	if (sheet == _spriteSheets.end()) {
		//Try to load the texture	
		SimpleSpriteSheet* spriteSheet = new SimpleSpriteSheet();
		spriteSheet->LoadTexture(texturePath.c_str());
		_spriteSheets[texturePath] = spriteSheet;
	}

	return true;
}

SimpleSpriteSheet* SimpleRenderer::GetSpriteSheet(SimpleID texturePath) {
	auto sheet = _spriteSheets.find(texturePath);
	if (sheet == _spriteSheets.end())
		return nullptr;
	return sheet->second;

}

bool SimpleRenderer::CreateSpriteAnimation(std::string name, std::string spriteSheet, std::vector<int> &frames, float frameTime) {

	//Check if it doesn't exist already

	if (_spriteAnimations.find(name) == _spriteAnimations.end()) {
		SimpleSpriteAnimation* anim = new SimpleSpriteAnimation();
		anim->SetAnimationName(name);
		anim->SetSpriteSheet(spriteSheet);
		anim->SetFrames(frames);
		anim->SetFrameTime(frameTime);
		_spriteAnimations[name] = anim;
		return true;
	}

	return true;

}

bool SimpleRenderer::CreateSpriteAnimation(std::string name) {

	//Check if it doesn't exist already

	if (_spriteAnimations.find(name) == _spriteAnimations.end()) {
		SimpleSpriteAnimation* anim = new SimpleSpriteAnimation();
		anim->SetAnimationName(name);
		_spriteAnimations[name] = anim;
		return true;
	}
	return true;

}


SimpleSpriteAnimation* SimpleRenderer::GetSpriteAnimation(SimpleID name) {
	auto it = _spriteAnimations.find(name);
	
	if (it == _spriteAnimations.end())
		return nullptr;

	return it->second;
}


bool SimpleRenderer::_LoadDefaultShaders() {

	if (!CreateProgram("VertexColor", "./shaders/SimpleColorShader.vert", "./shaders/SimpleColorShader.frag"))
		return false;

	if (!CreateProgram("VertexSprite", "./shaders/SimpleSpriteShader.vert", "./shaders/SimpleSpriteShader.frag"))
		return false;

	if (!CreateProgram("TextSprite", "./shaders/SimpleTextShader.vert", "./shaders/SimpleTextShader.frag"))
		return false;

	return true;

}



bool SimpleRenderer::LoadFont(std::string fontName, uint32_t size) {
	//Font managemente
	FT_Library _fontLib;
	if (FT_Init_FreeType(&_fontLib))
		SIMPLE_LOG("FREETYPE: Could not init FreeType Library");

	FT_Face face;
	std::string resPath = SimpleEngine::Instance()->GetResourcesBaseDir() + fontName;

	if (FT_New_Face(_fontLib, resPath.c_str(), 0, &face)) {
		SIMPLE_LOG("FREETYPE: Failed to load font : %s", fontName);
		return false;
	}


	//Load the characters for the font
	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Single channel textures
	FontCharacters chars;
	//Compute max char size
	glm::ivec2 maxFontSize = {1,1};

	chars.resize(128);

	for (uint8_t c = 0; c < 128; c++) //Currently we only load the first 128 ascii chars
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			SIMPLE_LOG("FREETYTPE: Failed to load Glyph %c", c);
			continue;
		}

		// Generate texture
		SimpleTexture* tex = new SimpleTexture();
		tex->LoadTextureFromMemory(face->glyph->bitmap.buffer, 1, face->glyph->bitmap.width, face->glyph->bitmap.rows);
		maxFontSize.x = std::max(maxFontSize.x, (int32_t)face->glyph->bitmap.width);
		maxFontSize.y = std::max(maxFontSize.y, (int32_t)face->glyph->bitmap.rows);

		// Now store character for later use
		chars[c] = {
			tex,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};

	}
	float scale = 1.0f / (float)std::max(maxFontSize.x, maxFontSize.y);
	_fonts[fontName] = std::make_pair(scale, chars);
	FT_Done_Face(face);
	FT_Done_FreeType(_fontLib);
	return true;
}
bool SimpleRenderer::HasFont(SimpleID fontName) {

	return _fonts.find(fontName) != _fonts.end();

}

SimpleRenderer::FontCharacters SimpleRenderer::GetFontChars(SimpleID fontName) {

	SIMPLE_ASSERT(HasFont(fontName));
	return _fonts[fontName].second;
	
}


float SimpleRenderer::GetFontScale(SimpleID fontName) {

	SIMPLE_ASSERT(HasFont(fontName));
	return _fonts[fontName].first;

}

//Serializes the currently loaded resources
bool SimpleRenderer::SerializeResources(std::string dir) {

	//Programs and textures aren't serialized
	json spriteSheets = json::array();
	path p = dir + +"/spriteSheets/";
	remove_all(p);
	create_directory(p);

	for (auto &sheet : _spriteSheets) {
		
		std::string  filename=   sheet.second->GetPath();
		std::replace(filename.begin(), filename.end(), '/', '_');
		filename = p.generic_string() +  filename + ".sheet";
		
		std::ofstream out(filename);
		
		if (!out.is_open()) {
			SIMPLE_LOG("Couldn't serialize spritesheets");
			return false;
		}	
		json sprSheet = sheet.second->Serialize();
		out << std::setw(4) << sprSheet;
		out.close();
	}

	p = dir + "/animations/";
	remove_all(p);
	create_directory(p);

	for (auto &anim: _spriteAnimations) {
		
		std::string  filename = anim.second->GetAnimationName();
		std::replace(filename.begin(), filename.end(), '/', '_');
		filename = p.generic_string() + filename + ".anim";

		std::ofstream out(filename);

		if (!out.is_open()) {
			SIMPLE_LOG("Couldn't serialize animations");
			return false;
		}
		json sprAnim = anim.second->Serialize();
		out << std::setw(4) << sprAnim;
		out.close();
	}

	return true;
}



bool SimpleRenderer::DeserializeResources(std::string dir) {

	//Load spriteSheets
	path p = dir + "/spriteSheets/";
	for (const auto& entry : directory_iterator{ p })
	{
		if (is_regular_file(entry.status()))
		{
			std::ifstream in(entry.path().generic_string());
			if (!in.is_open())
				return false;
			
			json sprSheet;
			in >> sprSheet;
			SimpleSpriteSheet* sheet = new SimpleSpriteSheet();
			sheet->Deserialize(sprSheet);
			_spriteSheets[sheet->GetPath()] = sheet;
			in.close();
		}
		else if (is_directory(entry.status()))
		{
			SIMPLE_LOG("Skipping directory %s",entry.path());
		}
	}


	p = dir + "/animations/";

	for (const auto& entry : directory_iterator{ p })
	{
		if (is_regular_file(entry.status()))
		{
			std::ifstream in(entry.path().generic_string());
			if (!in.is_open())
				return false;

			json sprAnim;
			in >> sprAnim;
			SimpleSpriteAnimation* anim = new SimpleSpriteAnimation();
			anim->Deserialize(sprAnim);
			_spriteAnimations[anim->GetAnimationName()] = anim;
			in.close();
		}
		else if (is_directory(entry.status()))
		{
			SIMPLE_LOG("Skipping directory %s", entry.path());
		}
	}

	return true;
}