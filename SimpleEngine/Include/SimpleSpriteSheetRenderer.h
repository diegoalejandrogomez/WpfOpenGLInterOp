#pragma once
#include "stdafx.h"
#include "SimpleObject.h"
#include "VertexFormats.h"
#include "SimpleCamera2D.h"
#include "SimpleMesh.h"
#include "SimpleTexture.h"
#include "SimpleSpriteRenderer.h"
#include "SimpleSpriteSheetRenderer.h"
#include "SimpleSpriteSheet.h"
#include "SimpleConfiguration.h"

class SimpleShaderProgram;


class SIMPLE_API SimpleSpriteSheetRenderer : public SimpleSpriteRenderer {
public:

	SimpleSpriteSheetRenderer();
	~SimpleSpriteSheetRenderer();
	virtual void Advance(float dt);
	virtual void Render(float dt);

	void SetSpriteSheet(SimpleID sheetName);
	void SetSpriteSheet(SimpleSpriteSheet* sheet);
	SimpleSpriteSheet* GetSpriteSheet() { return _spriteSheet; }
	void SetIndex(int pos);
	int GetIndex() { return _pos; }
	
	virtual SimpleID GetType() { return "SimpleSpriteSheetRenderer"; }
	
	json Serialize() override;
	bool Deserialize(const json &node) override;
protected:
		
	void _UpdateFrame();

	int _pos;
	SimpleSpriteSheet* _spriteSheet = nullptr;
	
	//Register to parent factory
	static SimpleObject::DerivedRegister<SimpleSpriteSheetRenderer> _regEntry;
	
};
	