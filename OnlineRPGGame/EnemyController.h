#pragma once
#include "SimplePlayerController.h"
#include "SimpleEngine.h"
class EnemyController : public SimplePlayerController {

public:

	EnemyController();
	~EnemyController();
	virtual void Advance(float dt) override;
	virtual void Render(float dt) override;
private:
	int index = 0;
};
