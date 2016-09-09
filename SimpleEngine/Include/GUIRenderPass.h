#pragma once


#include "RenderPass.h"

class SIMPLE_API GUIRenderPass: public RenderPass {

public:

	void Render(float dt, SimpleScene* scene);
};

