#pragma once
#include <tuple>

class SimpleObject {

public:

	virtual void Advance(float dt) = 0;
	virtual void Render(float dt) = 0;

};
