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
		
private:
	SimpleSpriteSheetRenderer* _spriteRenderer;
};
