#pragma once
#include "SimpleSerializable.h"
#include "SimpleConfiguration.h"

class SIMPLE_API SimpleGameLogic : public SimpleSerializable {
public:

	virtual void Init() = 0;
	virtual void Advance(float dt) = 0;
	virtual void Shutdown() = 0;
	virtual bool IsRunning() = 0;
	
};
