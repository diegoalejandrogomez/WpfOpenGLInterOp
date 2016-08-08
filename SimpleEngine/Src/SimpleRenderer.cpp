#include "stdafx.h"
#include "SimpleRenderer.h"
#include "SimpleScene.h"
#include "SimpleDispatcher.h"
#include <IL/il.h>
#include <IL/ilu.h>

SimpleRenderer::SimpleRenderer() {
	_deviceContext = nullptr;
	_renderingContext = nullptr;
	_hWnd = 0;
	_InitializeExtensions();
}

SimpleRenderer::~SimpleRenderer() {

	// Release the rendering context.
	if (_renderingContext)
	{
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(_renderingContext);
		_renderingContext = nullptr;
	}
};


void SimpleRenderer::Render(float dt, SimpleScene* scene ) {

	glViewport(0, 0, _width, _height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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

	_LoadDefaultShaders();
	
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

SimpleShaderProgram* SimpleRenderer::GetProgram(std::string name) const {
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

SimpleTexture* SimpleRenderer::GetTexture(std::string texturePath) {

	auto tex = _textures.find(texturePath);
	if (tex == _textures.end()) {
		//Try to load it
		if (LoadTexture(texturePath))
			return _textures[texturePath];
		return nullptr;
	}
	return tex->second;


}


bool SimpleRenderer::_LoadDefaultShaders() {

	if (!CreateProgram("VertexColor", "./shaders/SimpleColorShader.vert", "./shaders/SimpleColorShader.frag"))
		return false;

	if (!CreateProgram("VertexSprite", "./shaders/SimpleSpriteShader.vert", "./shaders/SimpleSpriteShader.frag"))
		return false;

	return true;

}