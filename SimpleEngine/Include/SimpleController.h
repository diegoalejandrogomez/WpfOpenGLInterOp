#pragma once
#include "SimpleConfiguration.h"
#include "SimpleObject.h"
#include "SimpleEvent.h"

class SimpleCharacter;

class SIMPLE_API SimpleController : public SimpleObject {

public:

	SimpleController() {}
	~SimpleController() {}

	virtual void Control(SimpleCharacter* character);
	virtual void Release(SimpleCharacter* character);
		
	void Advance(float dt) override;
	void Render(float dt) override;
	
	//Callbacks
	virtual void OnCharacterEvent(const SimpleEvent& event);
private:

	SimpleCharacter* _character = nullptr;

};
