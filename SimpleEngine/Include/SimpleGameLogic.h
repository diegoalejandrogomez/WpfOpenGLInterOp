#pragma once
#include "SimpleSerializable.h"
class SimpleGameLogic : public SimpleSerializable {
public:

	virtual void Init() = 0;
	virtual void Advance(float dt) = 0;
	virtual void Shutdown() = 0;
	virtual bool IsRunning() = 0;
	
};
