#pragma once
#include "SimpleConfiguration.h"
#include "SimpleObject.h"
#include "SimpleEvent.h"
class SimpleCharacter;

class SIMPLE_API SimpleController : public SimpleObject {

public:

	SimpleController() { }
	~SimpleController() {}

	virtual void Control(SimpleCharacter* character);
	virtual void Release(SimpleCharacter* character);
		
	virtual void Advance(float dt) override;
	virtual void Render(float dt) override;
	
	//Callbacks
	virtual void OnCharacterEvent(const SimpleEvent& event);

protected:
	
	void _RegisterDefaultListeners();
	void _UnregisterDefaultListeners();

	SimpleCharacter* _character = nullptr;

};
