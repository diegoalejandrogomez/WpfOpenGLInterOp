#pragma once
#include "stdafx.h"
#include "RenderPass.h"

class SIMPLE_API SimpleObjectsRenderPass : public RenderPass {

public:

	void Render(float dt, SimpleScene* scene);
};
