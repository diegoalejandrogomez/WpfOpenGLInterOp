#pragma once
#include "stdafx.h"
#include "RenderPass.h"
#include <queue>

class DebugRenderPass : public RenderPass {

	SimpleTextRenderer* _fpsText;
	static const uint32_t _nLog = 10;
	std::list<SimpleTextRenderer*> _log;

public:
	DebugRenderPass() {

		_fpsText = new SimpleTextRenderer();
		_fpsText->SetColor(SimpleColor::Yellow);
		_fpsText->SetFontName("fonts/arial.ttf");
		_fpsText->SetFontSize(15);
		
		SimpleDispatcher::Instance()->AddListener(LogEvent::descriptor, { this, [this](const SimpleEvent& evt) {
			const LogEvent* l = dynamic_cast<const LogEvent*>(&evt);
			AddLog(l->msg, SimpleColor::Yellow);
		} });
	}

	void AddLog(std::string msg, SimpleColor color) {
		if (_log.size() == _nLog) {
			delete _log.front();
			_log.pop_front();
		}

		SimpleTextRenderer* text = new SimpleTextRenderer();
		text->SetColor(color);
		text->SetFontName("fonts/arial.ttf");
		text->SetFontSize(15);
		text->SetText(msg);
		_log.push_back(text);
	}

	void Render(float dt, SimpleScene* scene) {
		
		float fps = SimpleEngine::Instance()->GetRenderFPS();
		char sfps[20];
		sprintf_s(sfps, 20,"FPS: %.2f", fps);
		_fpsText->SetText(sfps);

		//Position it relative to the camera
		SimpleCamera2D * cam = scene->GetCamera();
		
		glm::vec2 worldPos = cam->ScreenToWorld({ cam->GetWidth() - 50.0f ,15});
		glm::vec2 worldOrigin = cam->ScreenToWorld({ 0,0 });

		_fpsText->SetFontSize( worldOrigin.y - worldPos.y);
		_fpsText->SetPosition({ worldPos.x, worldPos.y, 0.0f });
		_fpsText->Render(dt);

		//Render log text
		uint32_t h = 15;
		for (auto text : _log) {
			
			glm::vec2 worldPos = cam->ScreenToWorld({ 0, h });
			glm::vec2 worldOrigin = cam->ScreenToWorld({ 0, h - 15 });

			text->SetFontSize(worldOrigin.y - worldPos.y);
			text->SetPosition({ worldPos.x, worldPos.y, 0.0f });
			text->Render(dt);
			h += 15;	
		}
	};

};