#pragma once
#include "SimpleConfiguration.h"
#include "SimpleNetworkObject.h"
#include <MessageIdentifiers.h>
#include <ReplicaManager3.h>
#include <NetworkIDManager.h>
#include <VariableDeltaSerializer.h>
#include <RakPeerInterface.h>
#include <NetworkIDObject.h>
#include "SimpleNetworkManager.h"
#include <GetTime.h>
#include "SimpleID.h"


class SimpleObject;

class SIMPLE_API SimpleNetworkSerializable {

public:
	virtual void StatusSerialize(RakNet::BitStream *stream) {};
	virtual void StatusDeserialize(RakNet::BitStream *stream) {};
	virtual void CreateSerialize(RakNet::BitStream *stream) {};
	virtual void CreateDeserialize(RakNet::BitStream *stream) {};
	virtual void DestroySerialize(RakNet::BitStream *stream) {};
	virtual void DestroyDeserialize(RakNet::BitStream *stream) {};

};

class SIMPLE_API SimpleNetworkObject : public RakNet::Replica3{

public:

	enum AUTH_OWNER {
		AUTH_SERVER,
		AUTH_LOCAL
	};

	SimpleNetworkObject() : _type(""){}
	~SimpleNetworkObject() {}
	
	void SetNetworkType(SimpleID type) { _type = type; }
	SimpleNetworkSerializable* GetOwner() { return _owner; };
	void SetOwner(SimpleNetworkSerializable* owner) { _owner = owner; };

	void SetAuthorityOwner(AUTH_OWNER authOwner) { _authOwner = authOwner; }
	AUTH_OWNER GetAuthorityOwner() { return _authOwner;};

	bool IsLocal() { return creatingSystemGUID == replicaManager->GetRakPeerInterface()->GetMyGUID(); }

	void Replicate();
	
private:
	SimpleID _type;
	SimpleNetworkSerializable* _owner;
	AUTH_OWNER _authOwner;

	virtual void WriteAllocationID(RakNet::Connection_RM3 *destinationConnection, RakNet::BitStream *allocationIdBitstream) const;
	virtual void SerializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection);
	virtual bool DeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *sourceConnection);
	virtual void SerializeDestruction(RakNet::BitStream *destructionBitstream, RakNet::Connection_RM3 *destinationConnection);
	virtual bool DeserializeDestruction(RakNet::BitStream *destructionBitstream, RakNet::Connection_RM3 *sourceConnection);
	virtual void DeallocReplica(RakNet::Connection_RM3 *sourceConnection);
	virtual RakNet::RM3ConstructionState QueryConstruction(RakNet::Connection_RM3 *destinationConnection, RakNet::ReplicaManager3 *replicaManager3);
	virtual bool QueryRemoteConstruction(RakNet::Connection_RM3 *sourceConnection);
	virtual RakNet::RM3ActionOnPopConnection QueryActionOnPopConnection(RakNet::Connection_RM3 *droppedConnection) const;
	virtual RakNet::RM3QuerySerializationResult QuerySerialization(RakNet::Connection_RM3 *destinationConnection);
	virtual RakNet::RM3SerializationResult Serialize(RakNet::SerializeParameters *serializeParameters);
	virtual void Deserialize(RakNet::DeserializeParameters *deserializeParameters);
	virtual void OnPoppedConnection(RakNet::Connection_RM3 *droppedConnection);
	void NotifyReplicaOfMessageDeliveryStatus(RakNet::RakNetGUID guid, uint32_t receiptId, bool messageArrived);

};
