#include "stdafx.h"
#include "SimpleObject.h"
#include <glm\gtx\transform.hpp>
#include "SimpleDebug.h"
#include "SimplePhysics.h"
#include "SimpleEngine.h"
#include "SimpleScene.h"
#include "SimpleDebug.h"
#include "SimpleLayer.h"
SimpleObject::SimpleObject() :_name("") {

	_body = nullptr;
	_layer = nullptr;
}

void SimpleObject::SetOrientation(float&& orientation) { 
	SetOrientation(orientation); 
};
void SimpleObject::SetOrientation(float& orientation) { 

	_orientation = orientation; 
	if (HasPhysics()) {
		glm::vec3 center = _aabb.Center();
		_body->SetTransform({ center.x, center.y }, _orientation);
	}

};

void SimpleObject::SetPosition(const glm::vec3&& pos) { 
	SetPosition(pos);	
};

void SimpleObject::SetPosition(const glm::vec3& pos) { 
	_aabb.position = pos; 
	if (HasPhysics()) {
		glm::vec3 center = _aabb.Center();
		_body->SetTransform({ center.x, center.y }, _orientation);
	}
};

void SimpleObject::SetVelocity(glm::vec2 &&v) {
	SetVelocity(v);
}

void SimpleObject::SetVelocity(glm::vec2 &v) {
	if (HasPhysics()) {
		_body->SetLinearVelocity({ v.x, v.y });
	}
}


void SimpleObject::AddVelocity(glm::vec2 &&v) {
	AddVelocity(v);
}

void SimpleObject::AddVelocity(glm::vec2 &v) {
	if (HasPhysics()) {
		b2Vec2 oldVel= _body->GetLinearVelocity();
		oldVel.x += v.x;
		oldVel.y += v.y;
		_body->SetLinearVelocity(oldVel);
	}
}

glm::vec2 SimpleObject::GetVelocity() {
	if (HasPhysics()) {
		b2Vec2 v = _body->GetLinearVelocity();
		return{ v.x, v.y };
	}
	return{ 0.0f, 0.0f };
}

void SimpleObject::SetSize(const glm::vec2&& size) { 
	SetSize(size);	
};
void SimpleObject::SetSize(const glm::vec2& size) { 
	if (_aabb.size != size) {
		_aabb.size = size;
		if (HasPhysics())
			_CreateFixtures();
	}
};

void SimpleObject::AddForce(glm::vec2 &&force, glm::vec2 &&point) {
	AddForce(force, point);
}
void SimpleObject::AddForce(glm::vec2 &force, glm::vec2 &point) {
	if (HasPhysics()) {
		_body->ApplyForce({ force.x, force.y }, { point.x, point.y }, true);
	}
}
void SimpleObject::AddImpulse(glm::vec2 &&impulse, glm::vec2 &&point) {
	AddImpulse(impulse, point);
}
void SimpleObject::AddImpulse(glm::vec2 &impulse, glm::vec2 &point) {
	if (HasPhysics()) {
		_body->ApplyLinearImpulse({ impulse.x, impulse.y }, { point.x, point.y }, true);
	}
}


void SimpleObject::Advance(float dt) {

	//If we have physics... well... surrender to its behaviour
	if (HasPhysics()) {
		
		b2Vec2 pos = _body->GetPosition();
		_aabb.position.x = pos.x;
		_aabb.position.y = pos.y;
		_orientation = _body->GetAngle();
		if(_netObject!= nullptr && !_netObject->IsLocal())
			_CompensatePosition();
	}

};
void SimpleObject::Render(float dt) {


}


void SimpleObject::AddedToScene(SimpleScene* scene, SimpleLayer* layer) {
	if (HasPhysics())
		_body->SetActive(true);
	_layer = layer;
}


void SimpleObject::RemovedFromScene(SimpleScene* scene, SimpleLayer* layer) {
	if (HasPhysics())
		_body->SetActive(false);
	_layer = nullptr;

}

void SimpleObject::_DestroyPhysics() {

	if (_body != nullptr) {
		b2World* world = SimpleEngine::Instance()->GetPhysics()->GetNativeWorld();
		world->DestroyBody(_body);
		_body = nullptr;
	}
}

void SimpleObject::_DestroyFixtures() {

	b2Fixture* fixture = _body->GetFixtureList();
	if (fixture != nullptr) {
		_body->DestroyFixture(fixture);
		fixture = nullptr;
	}

}
void SimpleObject::InitStaticPhysics(bool isSensor) {

	_DestroyPhysics();
	
	
	b2World* world = SimpleEngine::Instance()->GetPhysics()->GetNativeWorld();
	b2BodyDef def;
	def.type = b2_staticBody;
	def.position.x = _aabb.Center().x;
	def.position.y = _aabb.Center().y;
	def.angle = _orientation;
	def.userData = this;	
	def.active = false;
	_body = world->CreateBody(&def);
	_CreateFixtures(0.0f, 0.0f, 0.0f, isSensor);

}
void SimpleObject::InitKinematicPhysics(bool isSensor) {
	
	b2World* world = SimpleEngine::Instance()->GetPhysics()->GetNativeWorld();
	b2BodyDef def;
	def.type = b2_kinematicBody;
	def.position.x = _aabb.Center().x;
	def.position.y = _aabb.Center().y;
	def.angle = _orientation;
	def.linearVelocity = { 0.0f, 0.0f };
	def.userData = this;
	def.active = false;

	_body = world->CreateBody(&def);
	_CreateFixtures(0.0f, 0.0f, 0.0f, isSensor);
}
void SimpleObject::InitDynamicPhysics(float density, float restitution, float friction, bool isSensor) {
	b2World* world = SimpleEngine::Instance()->GetPhysics()->GetNativeWorld();
	b2BodyDef def;
	def.type = b2_dynamicBody;
	def.position.x = _aabb.Center().x;
	def.position.y = _aabb.Center().y;
	def.angle = _orientation;
	def.linearVelocity = { 0.0f, 0.0f };
	def.userData = this;
	def.active = false;
	
	_body = world->CreateBody(&def);
	_CreateFixtures(1.0f, 0.0f, 0.0f, isSensor);
}

void SimpleObject::_CreateFixtures(float density , float restitution , float friction, bool isSensor ) {
	
	b2Fixture* old= _body->GetFixtureList();
	if (old != nullptr) { //Keep old values if we are recreating the shape
		density = old->GetDensity();
		restitution = old->GetRestitution();
		friction = old->GetRestitution();
		isSensor = old->IsSensor();
	}

	_DestroyFixtures();
	
	b2FixtureDef fixtureDef;

	b2PolygonShape _box;
	_box.SetAsBox(_aabb.size.x* 0.5f, _aabb.size.y *0.5f);
	
	fixtureDef.shape = &_box;
	fixtureDef.density = density;
	fixtureDef.restitution = restitution;
	fixtureDef.friction = friction;
	fixtureDef.isSensor = isSensor;
	b2Fixture* myFixture = _body->CreateFixture(&fixtureDef);
	
}

const glm::mat4 SimpleObject::GetTransform()const {
	//We don't have scale for now...
	return  glm::translate(_aabb.position) * glm::rotate(_orientation, glm::vec3(0.0f, 0.0f, 1.0f));

}

void SimpleObject::FixOrientation(bool value) {
	if (HasPhysics())
		_body->SetFixedRotation(value);
}

json SimpleObject::Serialize() {

	json ret{
			{"type", static_cast<SimpleID::Type>(this->GetType()) },
			{"name", static_cast<SimpleID::Type>(_name)},
			{"aabb",{
					{"position", {_aabb.position.x, _aabb.position.y, _aabb.position.z}},
					{"size", {_aabb.size.x, _aabb.size.y}}
					}
			},
			{"orientation", _orientation}
	};

	if (_name.HasString())
		ret["nameVerbose"] = _name.GetString();
	
	return ret;	
}

bool SimpleObject::Deserialize(const json &node) {
	return this->Deserialize(node, "");
}

bool SimpleObject::Deserialize(const json &node, std::string dir) {
	
	SIMPLE_ASSERT(node.find("name") != node.end());
	
	if (node.find("nameVerbose") != node.end())
		_name = _name.GetString();
	else
		_name = (SimpleID::Type)node["name"];

	SIMPLE_ASSERT(node.find("aabb") != node.end());

	_aabb.position.x = node["aabb"]["position"][0];
	_aabb.position.y = node["aabb"]["position"][1];
	_aabb.position.z = node["aabb"]["position"][2];

	_aabb.size.x = node["aabb"]["size"][0];
	_aabb.size.y = node["aabb"]["size"][1];

	SIMPLE_ASSERT(node.find("orientation") != node.end());

	_orientation = node["orientation"];

	return true;
	
}


bool SimpleObject::OnBeginCollision(SimpleContactInfo& contactInfo) {
	/*SIMPLE_LOG("BEGIN  -  Collided %s with %s at points {(%.2f, %.2f),(%.2f, %.2f)} with normal (%.2f, %.2f)", GetType().GetString().c_str(),
		contactInfo.other->GetType().GetString().c_str(),
		contactInfo.points[0].x, contactInfo.points[0].y,
		contactInfo.points[1].x, contactInfo.points[1].y,
		contactInfo.normal.x, contactInfo.normal.y);*/
	return false;
};


bool SimpleObject::OnEndCollision(SimpleContactInfo& contactInfo) {
	/*SIMPLE_LOG("END  -  Collided %s with %s at points {(%.2f, %.2f),(%.2f, %.2f)} with normal (%.2f, %.2f)", GetType().GetString().c_str(),
		contactInfo.other->GetType().GetString().c_str(),
		contactInfo.points[0].x, contactInfo.points[0].y,
		contactInfo.points[1].x, contactInfo.points[1].y,
		contactInfo.normal.x, contactInfo.normal.y);*/
	return false;
};


void SimpleObject::InitNetwork() {
	if (_netObject != nullptr)
		delete _netObject;
	
	_netObject = new SimpleNetworkObject();
	_netObject->SetNetworkType(GetType());
	_netObject->SetOwner(this);
	_netObject->SetAuthorityOwner(SimpleNetworkObject::AUTH_LOCAL);
}

void SimpleObject::Replicate() {
	_netObject->Replicate();
}

void SimpleObject::SetAsTrigger(uint32_t idx) {
	if (HasPhysics())
		_body->GetFixtureList()[idx].SetSensor(true);

}
void SimpleObject::ResetTrigger(uint32_t idx) {
	if (HasPhysics())
		_body->GetFixtureList()[idx].SetSensor(false);
}


//Network sync
void SimpleObject::StatusSerialize(RakNet::BitStream *stream) {
	
	stream->Write(_aabb.anchor);
	stream->WriteVector<float>(_aabb.position.x, _aabb.position.y, _aabb.position.z);
	stream->Write(_aabb.size.x);
	stream->Write(_aabb.size.y);
	
	if (_body != nullptr) {
		const b2Vec2 &v = _body->GetLinearVelocity();
		const b2Vec2 &p = _body->GetPosition();
		stream->Write(v.x);
		stream->Write(v.y);
		stream->Write(p.x);
		stream->Write(p.y);
	}
	
};
void SimpleObject::StatusDeserialize(RakNet::BitStream *stream) {

	glm::vec3 pos;
	glm::vec2 size;
	SimpleAABB::ANCHOR_POINT anchor;
	stream->Read(anchor);
	stream->ReadVector<float>(pos.x, pos.y, pos.z);
	stream->Read(size.x);
	stream->Read(size.y);

	SetAnchor(anchor);
	if (_body != nullptr) {
		b2Vec2 v, p;
		stream->Read(v.x);
		stream->Read(v.y);
		stream->Read(p.x);
		stream->Read(p.y);

		SetVelocity({v.x, v.y});
		_netPosition.x = p.x;
		_netPosition.y = p.y;
	}
	else {
		SetPosition(pos); //If we don't have a physics body
	}	
	SetSize(size);
}

void SimpleObject::_CompensatePosition() {

	glm::vec3 deltaPos;
	glm::vec2 finalV(0.0f);
	
	deltaPos = _netPosition - glm::vec3{ _body->GetPosition().x, _body->GetPosition().y, 0.0f };
	if (deltaPos.length() > 0.5) {
		finalV = glm::vec2{ deltaPos.x , deltaPos.y } *_netSpatialRecoverySpeed;
		AddVelocity(finalV);
	}

	

}
void SimpleObject::CreateSerialize(RakNet::BitStream *stream) {
	//We can only replicate if the simpleobject exists in a scene

	stream->Write(_aabb.anchor);
	stream->WriteVector<float>(_aabb.position.x, _aabb.position.y, _aabb.position.z);
	stream->Write(_aabb.size.x);
	stream->Write(_aabb.size.y);
	stream->Write((uint32_t)_name);
	
	SIMPLE_ASSERT(_layer != nullptr);
	uint32_t n = _layer->GetName();
	stream->Write(n);
	

	//Serialize physics body
	if (_body != nullptr) {
		stream->Write(true); //signal we are going to send rb data
		stream->Write(_body->GetType());
		stream->Write(_wantsCollisions);
		b2Fixture* f = &_body->GetFixtureList()[0];
		stream->Write(f->IsSensor());
		stream->Write(f->GetDensity());
		stream->Write(f->GetFriction());
		stream->Write(f->GetRestitution());
		stream->Write(_body->IsFixedRotation());
	}
	else {
		stream->Write(false);
	}
	
}

void SimpleObject::CreateDeserialize(RakNet::BitStream *stream) {

	stream->Read(_aabb.anchor);
	stream->ReadVector<float>(_aabb.position.x, _aabb.position.y, _aabb.position.z);
	stream->Read(_aabb.size.x);
	stream->Read(_aabb.size.y);
	uint32_t name;
	stream->Read(name);
	_name = name;

	stream->Read(name);
	_layer = SimpleEngine::Instance()->GetScene()->GetLayer(SimpleID(name));
	SIMPLE_ASSERT(_layer != nullptr);
	
	bool hasBody;
	stream->Read(hasBody);

	//Serialize physics body
	if (hasBody) {

		b2BodyType type;
		stream->Read(type);
		stream->Read(_wantsCollisions);
		bool isSensor;
		stream->Read(isSensor);
		float density, friction, restitution;
		stream->Read(density);
		stream->Read(friction);
		stream->Read(restitution);
		bool fixedRotation;
		stream->Read(fixedRotation);

		switch (type)
		{
		case b2_staticBody:
			InitStaticPhysics(isSensor);
			break;
		case b2_kinematicBody:
			InitKinematicPhysics(isSensor);
			break;
		case b2_dynamicBody:
			InitDynamicPhysics(density, restitution, friction, isSensor);
			break;
		default:
			break;
		}
		_body->SetFixedRotation(fixedRotation);
		SimpleEngine::Instance()->GetScene()->AddEntity(this, _layer);
		
	}
	
}