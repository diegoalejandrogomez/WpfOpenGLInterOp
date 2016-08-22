#pragma once
#include "SimpleConfiguration.h"
class SimpleScene;

class SIMPLE_API RenderPass {

public:
	//We pass the dt just in case the rendering is animating something
	virtual void Render(float dt, SimpleScene* scene) = 0;


};
