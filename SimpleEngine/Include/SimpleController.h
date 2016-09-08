#pragma once
#include "SimpleConfiguration.h"

class SimpleCharacter;

class SIMPLE_API SimpleController {

	SimpleController() {}
	~SimpleController() {}

	void Control(SimpleCharacter* character);
	void Release(SimpleCharacter* character);
	
	void Update(float dt);
		

private:

	SimpleCharacter* _character = nullptr;

};
