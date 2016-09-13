#include "stdafx.h"
#include "SimpleObject.h"
#include <glm\gtx\transform.hpp>
#include "SimpleDebug.h"
#include "SimplePhysics.h"
#include "SimpleEngine.h"
#include "SimpleScene.h"

SimpleObject::SimpleObject() :_name("") {

	_body = nullptr;

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
	if (HasPhysics())
		_body->SetLinearVelocity({ v.x, v.y });
}
glm::vec2 SimpleObject::GetVelocity() {
	if (HasPhysics()) {
		b2Vec2 v = _body->GetLinearVelocity();
		return{ v.x, v.y };
	}
	return{ 0.0f, 0.0f };
}

void SimpleObject::SetSize(glm::vec2&& size) { 
	SetSize(size);	
};
void SimpleObject::SetSize(glm::vec2& size) { 

	_aabb.size = size; 
	if (HasPhysics())
		_CreateFixtures();
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
	}

};
void SimpleObject::Render(float dt) {


}


void SimpleObject::AddedToScene(SimpleScene* scene) {
	if (HasPhysics())
		_body->SetActive(true);
}


void SimpleObject::RemovedFromScene(SimpleScene* scene) {
	if (HasPhysics())
		_body->SetActive(false);
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
void SimpleObject::InitStaticPhysics() {

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
	_CreateFixtures(0.0f);

}
void SimpleObject::InitKinematicPhysics() {
	
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
	_CreateFixtures(0.0f);
}
void SimpleObject::InitDynamicPhysics(float density, float restitution, float friction) {
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
	_CreateFixtures(1.0f);
}

void SimpleObject::_CreateFixtures(float density , float restitution , float friction ) {
	
	b2Fixture* old= _body->GetFixtureList();
	if (old != nullptr) { //Keep old values if we are recreating the shape
		density = old->GetDensity();
		restitution = old->GetRestitution();
		friction = old->GetRestitution();
	}

	_DestroyFixtures();
	
	b2FixtureDef fixtureDef;

	b2PolygonShape _box;
	_box.SetAsBox(_aabb.size.x* 0.5f, _aabb.size.y *0.5f);
	
	fixtureDef.shape = &_box;
	fixtureDef.density = density;
	fixtureDef.restitution = restitution;
	fixtureDef.friction = friction;
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