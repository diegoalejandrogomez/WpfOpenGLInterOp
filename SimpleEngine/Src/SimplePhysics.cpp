#include "stdafx.h"
#include "SimplePhysics.h"
#include <Box2D\Box2D.h>

SimplePhysics::SimplePhysics() {
	_world = nullptr;
	_gravity = glm::vec2(0.0);
}
SimplePhysics::~SimplePhysics() {


}


void SimplePhysics::Initialize() {

	_world = new b2World({ _gravity.x, _gravity.y });
	_world->SetContactListener(this);

}
void SimplePhysics::Shutdown() {
	
	delete _world; //Frees everything inside. Be careful with invalid pointers
	_world = nullptr;
}

void SimplePhysics::Advance(float dt) {

	_world->Step(dt, _velocityIterations, _positionIterations);
	_world->ClearForces();
}

void SimplePhysics::DebugRender(float dt) {

	_world->DrawDebugData();

}

void SimplePhysics::AddDebugRender(b2Draw* d) {
	_world->SetDebugDraw(d);
	
}


b2World* SimplePhysics::GetNativeWorld() {

	return _world;
}

void SimplePhysics::BeginContact(b2Contact* contact)
{
	
}
void SimplePhysics::EndContact(b2Contact* contact)
{ 
}
void SimplePhysics::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{ /* handle pre-solve event */
}
void SimplePhysics::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{ /* handle post-solve event */}