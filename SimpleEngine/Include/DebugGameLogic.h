#pragma once
#include "SimpleGameLogic.h"
#include "json.hpp"
using json = nlohmann::json;

class SIMPLE_API DebugGameLogic : public SimpleGameLogic {
	
	// Inherited via SimpleGameLogic
	virtual void Init() override;
	
	virtual void Advance(float dt) override;

	virtual void Shutdown() override;

	virtual bool IsRunning() override;

	virtual json Serialize() override;

	virtual bool Deserialize(const json &node) override;

private:

	void _CreateTestScene();
	

};

