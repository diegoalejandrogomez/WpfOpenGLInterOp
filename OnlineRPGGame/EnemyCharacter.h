#pragma once
#include <vector>
#include <gl\GL.h>
#include <Windows.h>
#include "SimpleCharacter.h"

#include <string>
class EnemyCharacter : public SimpleCharacter {
public:
	EnemyCharacter();
	~EnemyCharacter();

	virtual void Initialize() override;
};
