#pragma once
#include <vector>
#include "SimpleSpriteRenderer.h"
#include "SimpleObject.h"
#include "SimpleAnimator.h"
#include "SimpleSpriteAnimation.h"
#include "SimpleController.h"
#include "SimpleAnimatedEntity.h"
#include <string>
class SIMPLE_API SimpleCharacter : public SimpleAnimatedEntity {
public:
		SimpleCharacter();
		~SimpleCharacter();
		
		virtual void Render(float dt) override;
		virtual void Advance(float dt) override;
		virtual void Die();
		virtual void Initialize() {};
		int GetSpeed();
		void SetSpeed(int);

		virtual SimpleID GetType() { return "SimpleCharacter"; }
		//Network sync
		virtual void StatusSerialize(RakNet::BitStream *stream);
		virtual void StatusDeserialize(RakNet::BitStream *stream);
		virtual void CreateSerialize(RakNet::BitStream *stream);
		virtual void CreateDeserialize(RakNet::BitStream *stream);
protected:
	SimpleController* _controller = nullptr;
	int speed = 0;
};
