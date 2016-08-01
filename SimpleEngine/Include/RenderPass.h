#pragma once
class SimpleScene;

class RenderPass {

public:
	//We pass the dt just in case the rendering is animating something
	virtual void Render(float dt, SimpleScene* scene) = 0;


};
