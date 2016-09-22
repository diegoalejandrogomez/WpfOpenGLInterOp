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
		
		//Physics callbacks
		virtual bool OnBeginCollision(SimpleContactInfo& contactInfo);
		virtual bool OnEndCollision(SimpleContactInfo& contactInfo);

		virtual void Initialize() override;
};
