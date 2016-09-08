#pragma once
#include "SimpleConfiguration.h"
#include "SimpleController.h"

class SIMPLE_API SimplePlayerController : public SimpleController {

public:

	SimplePlayerController() {}
	~SimplePlayerController() {}

	virtual void Advance(float dt) override;
	virtual void Render(float dt) override;

	//Callbacks
	virtual void OnCharacterEvent(const SimpleEvent& event);
private:



};



