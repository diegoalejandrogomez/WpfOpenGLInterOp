#include "stdafx.h"
#include "SimpleFixedObject.h"
#include "SimpleEngine.h"

//FACTORY_REGISTER(SimpleObject, SimpleFixedObject)

SimpleFixedObject::SimpleFixedObject()
{
	this->_spriteRenderer = new SimpleSpriteSheetRenderer();
	
}

SimpleFixedObject::~SimpleFixedObject()
{
	delete _spriteRenderer;
}


void SimpleFixedObject::Initialize()
{
	this->_spriteRenderer->SetSpriteSheet("tree/image1.png");
	this->_spriteRenderer->SetIndex(rand() % 4);
	this->_spriteRenderer->SetPosition(glm::vec3(rand() % 600 * (rand() % 2 == 0 ? 1 : -1) , rand() % 300 * (rand() % 2 == 0 ? 1 : -1), 0));
	this->_spriteRenderer->SetSize({ 100, 100 });
}

void SimpleFixedObject::Advance(float dt)
{
	this->_spriteRenderer->Advance(dt);
}

void SimpleFixedObject::Render(float dt)
{
	this->_spriteRenderer->Render(dt);
}