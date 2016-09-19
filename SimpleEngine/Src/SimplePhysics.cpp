#include "stdafx.h"
#include "SimplePhysics.h"
#include "SimpleObject.h"
#include "SimpleContactInfo.h"
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
	SimpleObject* firstObject = static_cast<SimpleObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
	SimpleObject* secondObject = static_cast<SimpleObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

	//Fill up proxy collision info
	SimpleContactInfo info;
	b2WorldManifold manifold;
	contact->GetWorldManifold(&manifold);

	info.points[0] = { manifold.points[0].x, manifold.points[0].y };
	info.points[1] = { manifold.points[1].x, manifold.points[1].y };
	info.normal = { manifold.normal.x, manifold.normal.y};
		
	if (firstObject->WantsCollisionCallback()) {
		info.other = secondObject;
		if (!firstObject->OnBeginCollision(info)) {
		
			if (secondObject->WantsCollisionCallback()) {
				info.other = firstObject;
				firstObject->OnBeginCollision(info);
			}
		
		}
	}
	else {
		if (secondObject->WantsCollisionCallback()) {
			info.other = firstObject;
			firstObject->OnBeginCollision(info);
		}
	}
}
void SimplePhysics::EndContact(b2Contact* contact)
{ 

	SimpleObject* firstObject = static_cast<SimpleObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
	SimpleObject* secondObject = static_cast<SimpleObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

	//Fill up proxy collision info
	SimpleContactInfo info;
	//On end contact the contact manifold doesn't exist anymore, so we don't fill that info

	if (firstObject->WantsCollisionCallback()) {
		info.other = secondObject;
		if (!firstObject->OnEndCollision(info)) {

			if (secondObject->WantsCollisionCallback()) {
				info.other = firstObject;
				firstObject->OnEndCollision(info);
			}

		}
	}
	else {
		if (secondObject->WantsCollisionCallback()) {
			info.other = firstObject;
			firstObject->OnEndCollision(info);
		}
	}


}
void SimplePhysics::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{ /* handle pre-solve event */
}
void SimplePhysics::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{ /* handle post-solve event */
}
