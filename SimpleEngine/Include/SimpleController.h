#pragma once
#include "SimpleConfiguration.h"
#include "SimpleObject.h"

class SimpleCharacter;

class SIMPLE_API SimpleController : public SimpleObject {

public:

	SimpleController() {}
	~SimpleController() {}

	void Control(SimpleCharacter* character);
	void Release(SimpleCharacter* character);
		
	void Advance(float dt) override;
	void Render(float dt) override;
	
	//Callbacks
	virtual void OnCharacterControlled() {};
	virtual void OnCharacterReleased() {};
	virtual void OnCharacterDamaged() {};
	virtual void OnCharacterDied() {};
	virtual void OnCharacterCollition() {};
		

private:

	SimpleCharacter* _character = nullptr;

};
