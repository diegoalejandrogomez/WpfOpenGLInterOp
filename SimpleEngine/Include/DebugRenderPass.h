#pragma once
#include "stdafx.h"
#include "RenderPass.h"

class DebugRenderPass : public RenderPass {

public:

	void Render() {
		// Set the color to clear the screen to.
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

		// Clear the screen and depth buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	};

};