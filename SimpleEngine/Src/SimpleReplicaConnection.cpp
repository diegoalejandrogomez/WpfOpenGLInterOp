#include "stdafx.h"
#include "SimpleReplicaConnection.h"
#include "SimpleObject.h"

Replica3 *SimpleReplicaConnection::AllocReplica(RakNet::BitStream *allocationId, ReplicaManager3 *replicaManager3)
{
	uint32_t type;
	allocationId->Read(type);
	SimpleObject * obj = SimpleObject::BaseFactory::CreateInstance(type);
	obj->InitNetwork();
	if (obj != nullptr)
		return obj->GetNetworkObject();
	return nullptr;


}
