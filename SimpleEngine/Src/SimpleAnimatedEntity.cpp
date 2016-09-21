#include "stdafx.h"
#include "SimpleAnimatedEntity.h"
#include "SimpleDispatcher.h"
#include "SimpleEngine.h"

//FACTORY_REGISTER(SimpleObject, SimpleAnimatedEntity)

SimpleAnimatedEntity::SimpleAnimatedEntity()
{
	_animator = new SimpleAnimator();
}

SimpleAnimatedEntity::~SimpleAnimatedEntity()
{
	delete _animator;
}

void SimpleAnimatedEntity::AddAnimation(std::string stateName, SimpleAnimatedSpriteRenderer* animation)
{
	this->_animator->AddAnimation(stateName, animation);
}

void SimpleAnimatedEntity::RemoveAnimation(std::string stateName)
{
	this->_animator->RemoveAnimation(stateName);
}

void SimpleAnimatedEntity::Advance(float dt) {
	SimpleObject::Advance(dt);
}

void SimpleAnimatedEntity::Render(float dt)
{
	auto currentAnimation = this->_animator->GetCurrentState();
	if (currentAnimation != nullptr) {
		currentAnimation->SetPosition(this->GetPosition());
		auto size = this->GetSize();
		currentAnimation->SetSize(size);
		float orientation = GetOrientation();
		currentAnimation->SetOrientation(orientation);
		currentAnimation->Render(dt);
		currentAnimation->Advance(dt);
	}
}

void SimpleAnimatedEntity::ChangeAnimationState(std::string newState)
{
	this->_animator->SwitchState(newState);
}


void SimpleAnimatedEntity::StatusSerialize(RakNet::BitStream *stream) {
	SimpleObject::StatusSerialize(stream);
	if (_animator->GetCurrentState()->IsPlaying())
		stream->Write(RakNet::RakString(_animator->GetCurrentStateName().c_str()));
	
}

void SimpleAnimatedEntity::StatusDeserialize(RakNet::BitStream *stream) {
	SimpleObject::StatusDeserialize(stream);
	RakNet::RakString state;
	if(stream->Read(state))
		_animator->SwitchState(state.C_String());

}
//This method assumes that the resource already exist on the other side
void SimpleAnimatedEntity::CreateSerialize(RakNet::BitStream *stream) {
	SimpleObject::CreateSerialize(stream);

	auto _animations = _animator->GetAnimations();
	stream->Write(_animations->size());
	auto animIt = _animations->begin();
	while (animIt != _animations->end()) {
		stream->Write(RakNet::RakString(animIt->first.c_str()));
		stream->Write(RakNet::RakString(animIt->second->GetAnimation()->GetAnimationName().c_str()));
		++animIt;
	}
}
void SimpleAnimatedEntity::CreateDeserialize(RakNet::BitStream *stream) {
	SimpleObject::CreateDeserialize(stream);

	uint32_t animCount;
	stream->Read(animCount);

	for (int i = 0; i < animCount; ++i) {
		RakNet::RakString name, anim;
		stream->Read(name);
		stream->Read(anim);
		auto animation = SimpleEngine::Instance()->GetResourceManager()->GetSpriteAnimation(anim.C_String());
		SimpleAnimatedSpriteRenderer* animatedSpriteRenderer = new SimpleAnimatedSpriteRenderer();
		animatedSpriteRenderer->SetAnimation(animation);
		AddAnimation(name.C_String(), animatedSpriteRenderer);
	}
}