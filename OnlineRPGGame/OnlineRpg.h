#pragma once
#include "SimpleEngine.h"
#include "HeroCharacter.h"
#include "SimpleLayer.h"
#include "SimpleFixedObject.h"

class OnlineRpg : public SimpleGameLogic{
public:
	OnlineRpg();
	~OnlineRpg();
	// Inherited via SimpleGameLogic
	virtual void Init() override;
	virtual void Advance(float dt) override;
	virtual void Shutdown() override;
	virtual bool IsRunning() override;
	virtual json Serialize() override;
	virtual bool Deserialize(const json &node) override;


	void RunAsServer() { _isServer = true; };
	void RunAsClient() { _isServer = false; };
private:
	HeroCharacter* _character;
	SimpleLayer* _layer;
	SimpleLayer* _layerBackground;

	bool _isServer = false;
};