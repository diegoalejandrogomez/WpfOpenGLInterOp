#include "stdafx.h"
#include "GUIRenderPass.h"
#include "SimpleEngine.h"
#include "SimpleGUI.h"

void GUIRenderPass::Render(float dt, SimpleScene* scene) {

	SimpleGUI * gui = SimpleEngine::Instance()->GetGUI();
	if(gui != nullptr)
		gui->Render(dt);
}

