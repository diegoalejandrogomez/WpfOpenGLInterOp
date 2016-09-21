#include "stdafx.h"
#include "SimpleFixedObject.h"
#include "SimpleEngine.h"

FACTORY_REGISTER(SimpleObject, SimpleFixedObject)

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
	this->_spriteRenderer->SetPosition(glm::vec3(rand() % 500 * (rand() % 2 == 0 ? 1 : -1) , rand() % 300 * (rand() % 2 == 0 ? 1 : -1), 0));
	this->_spriteRenderer->SetSize({ 100, 100 });
	SetSize({ 100,100 });
	SetPosition(_spriteRenderer->GetPosition());
	this->InitStaticPhysics();
}

void SimpleFixedObject::Advance(float dt)
{
	this->_spriteRenderer->Advance(dt);
}

void SimpleFixedObject::Render(float dt)
{
	this->_spriteRenderer->Render(dt);
}


void SimpleFixedObject::CreateSerialize(RakNet::BitStream *stream){

	SimpleObject::CreateSerialize(stream);
	RakNet::RakString str = _spriteRenderer->GetSpriteSheet()->GetPath().c_str();
	stream->Write(str); 
	stream->Write(_spriteRenderer->GetIndex());

}

void SimpleFixedObject::CreateDeserialize(RakNet::BitStream *stream) {
	SimpleObject::CreateDeserialize(stream);
	RakNet::RakString str;
	uint32_t idx;
	if (stream->Read(str)) {
		this->_spriteRenderer->SetSpriteSheet("tree/image1.png");
		
	}
	if (stream->Read(idx)) {
		this->_spriteRenderer->SetIndex(idx);
	}
		
	this->_spriteRenderer->SetPosition(GetPosition());
	this->_spriteRenderer->SetSize(GetSize());

}