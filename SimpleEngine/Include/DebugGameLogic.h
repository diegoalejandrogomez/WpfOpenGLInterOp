#pragma once
#include "SimpleGameLogic.h"
#include "json.hpp"
using json = nlohmann::json;

class DebugGameLogic : public SimpleGameLogic {
	
	// Inherited via SimpleGameLogic
	virtual void Init() override;
	
	virtual void Advance(float dt) override;

	virtual void Shutdown() override;

	virtual bool IsRunning() override;

	virtual json Serialize() override;

	virtual bool Deserialize(json &node) override;

private:

	void _CreateTestScene();
	

};

