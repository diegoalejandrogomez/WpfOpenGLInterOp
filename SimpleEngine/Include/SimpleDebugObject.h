#pragma once
#include "stdafx.h"
#include "SimpleObject.h"

class SimpleDebugObject : public SimpleObject{
public:

	SimpleDebugObject();
	void Advance(float dt);
	void Render(float dt);

private:

};
