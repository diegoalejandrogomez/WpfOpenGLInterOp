#pragma once
#include <vector>
#include "SimpleSpriteRenderer.h"
#include "SimpleObject.h"
#include "SimpleAnimator.h"
#include "SimpleSpriteAnimation.h"

#include <string>
class SIMPLE_API SimpleAnimatedEntity : public SimpleObject {
public:
		SimpleAnimatedEntity();
		~SimpleAnimatedEntity();
		
		void AddAnimation(std::string, SimpleAnimatedSpriteRenderer*);
		void RemoveAnimation(std::string);
		virtual void Render(float dt) override;
		virtual void Advance(float dt) override;
		
		virtual void Initialize() = 0;
		void ChangeAnimationState(std::string);

		virtual SimpleID GetType() { return "SimpleAnimatedEntity"; }

		virtual void StatusSerialize(RakNet::BitStream *stream);
		virtual void StatusDeserialize(RakNet::BitStream *stream);
		virtual void CreateSerialize(RakNet::BitStream *stream);
		virtual void CreateDeserialize(RakNet::BitStream *stream);

protected:
	SimpleAnimator* _animator;
};
