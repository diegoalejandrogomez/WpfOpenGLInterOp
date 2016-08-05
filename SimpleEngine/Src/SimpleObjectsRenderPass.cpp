#include "stdafx.h"
#include "SimpleObjectsRenderPass.h"
#include "SimpleScene.h"

void SimpleObjectsRenderPass::Render(float dt, SimpleScene* scene) {
	
	//Delegate rendering to the object for now...
	if (scene == nullptr)
		return;

	for (auto layer : scene->GetLayers()) {
		for (auto ent : layer->GetEntities()) {
			ent->Render(dt);
		}
	}
}