#pragma once
#include "stdafx.h"
#include "RenderPass.h"

class SimpleObjectsRenderPass : public RenderPass {

public:

	void Render(float dt, SimpleScene* scene);
};
