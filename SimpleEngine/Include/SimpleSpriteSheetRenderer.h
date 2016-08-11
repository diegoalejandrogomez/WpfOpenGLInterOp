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

class SimpleShaderProgram;

class SimpleSpriteSheetRenderer : public SimpleSpriteRenderer {
public:

	SimpleSpriteSheetRenderer();
	~SimpleSpriteSheetRenderer();
	virtual void Advance(float dt);
	virtual void Render(float dt);

	void SetSpriteSheet(std::string sheetName);
	void SetSpriteSheet(SimpleSpriteSheet* sheet);
	void SetIndex(int pos);

protected:
		
	int _pos;
	SimpleSpriteSheet* _spriteSheet = nullptr;
	
};

