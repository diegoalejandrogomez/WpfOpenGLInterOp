#include "stdafx.h"
#include "SimpleEngine.h"
#include "DebugRenderPass.h"

SimpleEngine::SimpleEngine() {


};

SimpleEngine::~SimpleEngine() {


};


void SimpleEngine::InitRenderer(HWND hWnd, uint32_t width, uint32_t height) {
	
	_renderer = new SimpleRenderer();
	_renderer->InitializeOpenGL(hWnd, width, height);

	_renderer->AddPass(new DebugRenderPass());
}

void SimpleEngine::Render(float dt) {
	
	if (_scene != nullptr)
		_scene->Render(dt);

}

void SimpleEngine::Advance(float dt) {
	
	if (_scene != nullptr)
		_scene->Advance(dt);

}
