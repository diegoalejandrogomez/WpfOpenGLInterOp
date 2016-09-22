#pragma once
#include <tuple>
#include <glm\glm.hpp>
#include "SimpleAABB.h"
#include "SimpleID.h"
#include "json.hpp"
#include "SimpleFactory.h"
#include "SimpleSerializable.h"
#include "SimpleConfiguration.h"
#include "SimpleContactInfo.h"
#include "SimpleNetworkObject.h"
#include <Box2D\Box2D.h>

using json = nlohmann::json;
class SimpleScene;
class SimpleLayer;

class SIMPLE_API SimpleObject :public SimpleFactory<SimpleObject>,
					public SimpleSerializable, public SimpleNetworkSerializable{

public:

	SimpleObject() ;
	virtual void Advance(float dt);
	virtual void Render(float dt);
	virtual void AddedToScene(SimpleScene* scene, SimpleLayer* layer);
	virtual void RemovedFromScene(SimpleScene* scene, SimpleLayer* layer);

	inline const glm::vec3& GetPosition() const { return _aabb.position; };
	inline const glm::vec2& GetSize() const { return _aabb.size; };
	inline const SimpleAABB::ANCHOR_POINT GetAnchor() const { return _aabb.anchor; };
	inline const float& GetOrientation() const { return _orientation; };
	inline const SimpleID& GetName() const { return _name; };

	inline void SetPosition(const glm::vec3&& pos);
	inline void SetPosition(const glm::vec3& pos);

	inline const void SetAnchor(SimpleAABB::ANCHOR_POINT anchor) { _aabb.anchor = anchor; }
	inline void SetSize(const glm::vec2&& size) ;
	inline void SetSize(const glm::vec2& size) ;

	inline void SetOrientation(float&& orientation);
	inline void SetOrientation(float& orientation);

	inline void SetVelocity(glm::vec2 &&v);
	inline void SetVelocity(glm::vec2 &v);
	inline void AddVelocity(glm::vec2 &&v);
	inline void AddVelocity(glm::vec2 &v);

	inline void AddForce(glm::vec2 &&force, glm::vec2 &&point);
	inline void AddForce(glm::vec2 &force, glm::vec2 &point);

	inline void AddImpulse(glm::vec2 &&impulse, glm::vec2 &&point);
	inline void AddImpulse(glm::vec2 &impulse, glm::vec2 &point);

	inline void FixOrientation(bool value);

	inline glm::vec2 GetVelocity();
	inline void SetName(SimpleID name) { _name = name; };
	

	void InitStaticPhysics(bool isSensor = false);
	void InitKinematicPhysics(bool isSensor = false);
	void InitDynamicPhysics(float density = 1.0f, float restitution = 0.0f, float friction = 0.0f, bool isSensor= false);
	bool HasPhysics() { return _body != nullptr; }
	void EnableCollisionCallback() { _wantsCollisions = true; }
	void DisableCollisionCallback() { _wantsCollisions = false; }
	bool WantsCollisionCallback() { return _wantsCollisions; }
	void SetAsTrigger(uint32_t idx = 0);
	void ResetTrigger(uint32_t idx = 0);

	
	//Physics callbacks
	virtual bool OnBeginCollision(SimpleContactInfo& contactInfo);
	virtual bool OnEndCollision(SimpleContactInfo& contactInfo);

	//Net
	void InitNetwork();
	void Replicate();
	SimpleNetworkObject* GetNetworkObject() { return _netObject; };

	inline const SimpleAABB& GetAABB()const { return _aabb; };
	//Not efficient... we could do a lot better
	const glm::mat4 GetTransform() const;
	virtual SimpleID GetType() { return "SimpleObject"; }
	
	json Serialize() override;
	bool Deserialize(const json& node) override;
	bool Deserialize(const json& node, std::string dir) override;


	//Network sync
	virtual void StatusSerialize(RakNet::BitStream *stream) ;
	virtual void StatusDeserialize(RakNet::BitStream *stream) ;
	virtual void CreateSerialize(RakNet::BitStream *stream) ;
	virtual void CreateDeserialize(RakNet::BitStream *stream);

protected:

	void _DestroyPhysics();
	void _CreateFixtures(float density = 1.0f, float restitution = 0.0f, float friction = 0.0f, bool isSensor = false);
	void _DestroyFixtures();
	void _CompensatePosition();

	//Layer info
	SimpleLayer* _layer;

	SimpleAABB _aabb;
	float _orientation	= 0.0f;
	SimpleID _name;

	//If the body exist in the physical world
	b2Body* _body = nullptr;
	bool _wantsCollisions = true;

	//For networking
	SimpleNetworkObject* _netObject = nullptr;
	static constexpr float _netSpatialRecoverySpeed = 1.0f;
	glm::vec3 _netPosition;
};
