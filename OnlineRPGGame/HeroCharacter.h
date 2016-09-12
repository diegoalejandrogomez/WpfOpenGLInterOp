#pragma once
#include <vector>
#include "SimpleSpriteRenderer.h"
#include "SimpleObject.h"
#include "SimpleAnimator.h"
#include "SimpleSpriteAnimation.h"
#include "SimpleController.h"
#include "SimpleAnimatedEntity.h"
#include "SimpleCharacter.h"

#include <string>
class SIMPLE_API HeroCharacter : public SimpleCharacter {
public:
		HeroCharacter();
		~HeroCharacter();
		
		virtual void Initialize() override;
};
