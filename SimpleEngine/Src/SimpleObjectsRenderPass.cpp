#include "stdafx.h"
#include "SimpleObjectsRenderPass.h"
#include "SimpleScene.h"

void SimpleObjectsRenderPass::Render(float dt, SimpleScene* scene) {
	
	//Delegate rendering to the object for now...
	if (scene == nullptr)
		return;

	//Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (auto layer : scene->GetLayers()) {
		for (auto ent : layer->GetEntities()) {
			ent->Render(dt);
		}
	}
}