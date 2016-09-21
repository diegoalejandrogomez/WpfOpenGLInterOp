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


	void RunAsServer(std::string ip) { _isServer = true; _ip = ip; };
	void RunAsClient(std::string ip) { _isServer = false; _ip = ip; };
private:
	HeroCharacter* _character;
	SimpleLayer* _layer;
	SimpleLayer* _layerBackground;

	bool _isServer = false;
	std::string _ip;
};