#pragma once
#include "stdafx.h"
#include "RenderPass.h"

class DebugRenderPass : public RenderPass {

	SimpleTextRenderer* _fpsText;

public:
	DebugRenderPass() {

		_fpsText = new SimpleTextRenderer();
		_fpsText->SetColor({ 255,255,0,255 });
		_fpsText->SetFontName("fonts/arial.ttf");
		_fpsText->SetFontSize(15);
	}

	void Render(float dt, SimpleScene* scene) {
		
		float fps = SimpleEngine::Instance()->GetRenderFPS();
		char sfps[20];
		sprintf_s(sfps, 20,"FPS: %.2f", fps);
		_fpsText->SetText(sfps);

		//Position it relative to the camera
		SimpleCamera2D * cam = scene->GetCamera();
		glm::vec2 worldPos = cam->ScreenToWorld({0,15});
		glm::vec2 worldOrigin = cam->ScreenToWorld({ 0,0 });

		_fpsText->SetFontSize( worldOrigin.y - worldPos.y);
		_fpsText->SetPosition({ worldPos.x, worldPos.y, 0.0f });
		_fpsText->Render(dt);
	};

};