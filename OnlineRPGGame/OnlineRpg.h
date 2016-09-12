#pragma once
#include "SimpleEngine.h"
#include "HeroCharacter.h"
#include "SimpleLayer.h"
#include "SimpleFixedObject.h"

class OnlineRpg {
public:
	OnlineRpg();
	~OnlineRpg();
	void Initialize();
private:
	HeroCharacter* _character;
	SimpleLayer* _layer;
	SimpleLayer* _layerBackground;
};