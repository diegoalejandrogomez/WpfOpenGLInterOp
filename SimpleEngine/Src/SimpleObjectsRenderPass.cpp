#include "stdafx.h"
#include "SimpleObjectsRenderPass.h"
#include "SimpleScene.h"

void SimpleObjectsRenderPass::Render(float dt, SimpleScene* scene) {
	
	//Delegate rendering to the object for now...
	if (scene == nullptr)
		return;

	for (auto ent : scene->GetEntities()) {
		ent->Render(dt);
	}

}