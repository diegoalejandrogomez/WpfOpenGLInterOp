#pragma once
#include "SimpleConfiguration.h"
#include "SimpleController.h"
#include "SimpleCharacter.h"

class SIMPLE_API SimplePlayerController : public SimpleController {

public:

	SimplePlayerController() {}
	~SimplePlayerController() {}

	virtual void Advance(float dt) = 0;
	virtual void Render(float dt) = 0;

	//Callbacks
	virtual void OnCharacterEvent(const SimpleEvent& event);

};



