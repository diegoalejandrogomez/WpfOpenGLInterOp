#pragma once
#include <Box2d/Box2D.h>
class SimpleObject;

class SimplePhysics final : public b2ContactListener {

public:



	SimplePhysics();
	~SimplePhysics();

	void Initialize();
	void Shutdown();

	void Advance(float dt);
	void DebugRender(float dt);
	void AddDebugRender(b2Draw *d);

	void SetGravity(glm::vec2 g) { _gravity = g; }
	glm::vec2 GetGravity() { return _gravity; }

	b2World* GetNativeWorld();

	//Contact Listener Interface
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	
private:

	b2World* _world;
	glm::vec2 _gravity;
	
	static constexpr int32_t _velocityIterations = 6;
	static constexpr int32_t _positionIterations = 4;

};
