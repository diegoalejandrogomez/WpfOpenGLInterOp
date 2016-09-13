#pragma once
#include "SimplePlayerController.h"
#include "SimpleEngine.h"
class HeroController : public SimplePlayerController {

public:

	HeroController();
	~HeroController();
	virtual void Advance(float dt) override;
	virtual void Render(float dt) override;

};
