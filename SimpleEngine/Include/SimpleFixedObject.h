#pragma once
#include <vector>
#include "SimpleSpriteSheetRenderer.h"
#include "SimpleObject.h"
class SIMPLE_API SimpleFixedObject : public SimpleObject {
public:
		SimpleFixedObject();
		~SimpleFixedObject();
		virtual void Advance(float dt) override;
		virtual void Render(float dt) override;
		virtual void Initialize(); // = 0
		virtual SimpleID GetType() { return "SimpleFixedObject"; }
		

		//Network sync
		virtual void CreateSerialize(RakNet::BitStream *stream)override ;
		virtual void CreateDeserialize(RakNet::BitStream *stream)override;
		
private:
	SimpleSpriteSheetRenderer* _spriteRenderer;
};
