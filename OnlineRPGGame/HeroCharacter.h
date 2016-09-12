#pragma once
#include <vector>
#include <gl\GL.h>
#include <Windows.h>
#include "SimpleCharacter.h"

#include <string>
class HeroCharacter : public SimpleCharacter {
public:
		HeroCharacter();
		~HeroCharacter();
		
		virtual void Initialize() override;
};
