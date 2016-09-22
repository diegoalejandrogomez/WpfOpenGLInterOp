#include "stdafx.h"
#include "SimpleEngine.h"


void SimpleNetworkObject::Replicate() {
	
	
	SimpleEngine::Instance()->GetNetwork()->Replicate(this);
}


void SimpleNetworkObject::Sync(NetworkID nID) {
	_authOwner = AUTH_STATIC;
	SimpleEngine::Instance()->GetNetwork()->Sync(this, nID);
}

void SimpleNetworkObject::WriteAllocationID(RakNet::Connection_RM3 *destinationConnection, RakNet::BitStream *allocationIdBitstream) const {
	allocationIdBitstream->Write((uint32_t)_type);
}

void SimpleNetworkObject::SerializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection) {
	_owner->CreateSerialize(constructionBitstream);
}
bool SimpleNetworkObject::DeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *sourceConnection) {
	_owner->CreateDeserialize(constructionBitstream);
	return true;
}
void SimpleNetworkObject::SerializeDestruction(RakNet::BitStream *destructionBitstream, RakNet::Connection_RM3 *destinationConnection) {
	_owner->DestroySerialize(destructionBitstream);
}
bool SimpleNetworkObject::DeserializeDestruction(RakNet::BitStream *destructionBitstream, RakNet::Connection_RM3 *sourceConnection) {
	_owner->DestroyDeserialize(destructionBitstream);
	return true;
}

void SimpleNetworkObject::SerializeConstructionExisting(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection) { 
	_owner->ExistingDeserialize(constructionBitstream);
}

/// Same as DeserializeConstruction(), but for an object that already exists on the remote system.
/// Used if you return RM3CS_ALREADY_EXISTS_REMOTELY from QueryConstruction
void SimpleNetworkObject::DeserializeConstructionExisting(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *sourceConnection) { 
	_owner->ExistingSerialize(constructionBitstream);
} 


void SimpleNetworkObject::DeallocReplica(RakNet::Connection_RM3 *sourceConnection) {
	delete this;
}

RakNet::RM3ConstructionState SimpleNetworkObject::QueryConstruction(RakNet::Connection_RM3 *destinationConnection, RakNet::ReplicaManager3 *replicaManager3) {
	SimpleNetworkManager* man = SimpleEngine::Instance()->GetNetwork();

	switch (_authOwner) {
	case  AUTH_LOCAL:
		return QueryConstruction_ClientConstruction(destinationConnection, man->IsServer());
		break;
	case AUTH_SERVER:
		return QueryConstruction_ServerConstruction(destinationConnection, man->IsServer());
		break;
	case AUTH_STATIC:
		return man->IsServer() ? RM3CS_ALREADY_EXISTS_REMOTELY : RM3CS_ALREADY_EXISTS_REMOTELY_DO_NOT_CONSTRUCT;
	}
}

bool SimpleNetworkObject::QueryRemoteConstruction(RakNet::Connection_RM3 *sourceConnection) {
	SimpleNetworkManager* man = SimpleEngine::Instance()->GetNetwork();
	if (_authOwner == AUTH_LOCAL)
		return QueryRemoteConstruction_ClientConstruction(sourceConnection, SimpleEngine::Instance()->GetNetwork()->IsServer());
	else
		return QueryRemoteConstruction_ServerConstruction(sourceConnection, SimpleEngine::Instance()->GetNetwork()->IsServer());
}

RakNet::RM3ActionOnPopConnection SimpleNetworkObject::QueryActionOnPopConnection(RakNet::Connection_RM3 *droppedConnection) const{
	
	switch (_authOwner)
	{
	case SimpleNetworkObject::AUTH_SERVER:
	case SimpleNetworkObject::AUTH_LOCAL:
		if (SimpleEngine::Instance()->GetNetwork()->IsServer()) 
			return QueryActionOnPopConnection_Server(droppedConnection);
		else 
			return QueryActionOnPopConnection_Client(droppedConnection);	
		break;
	case SimpleNetworkObject::AUTH_STATIC:
		return RM3AOPC_DO_NOTHING;
		break;
	}

	

}

RakNet::RM3QuerySerializationResult SimpleNetworkObject::QuerySerialization(RakNet::Connection_RM3 *destinationConnection) {
	switch (_authOwner)
	{
	case SimpleNetworkObject::AUTH_SERVER:
		return QuerySerialization_ServerSerializable(destinationConnection, SimpleEngine::Instance()->GetNetwork()->IsServer());
		break;
	case SimpleNetworkObject::AUTH_LOCAL:
		return QuerySerialization_ClientSerializable(destinationConnection, SimpleEngine::Instance()->GetNetwork()->IsServer());
		break;
	case SimpleNetworkObject::AUTH_STATIC:
		return RM3QSR_NEVER_CALL_SERIALIZE;
		break;
	}
	
}
RakNet::RM3SerializationResult SimpleNetworkObject::Serialize(RakNet::SerializeParameters *serializeParameters) {

	// Put all variables to be sent unreliably on the same channel, then specify the send type for that channel
	serializeParameters->pro[0].reliability = UNRELIABLE_WITH_ACK_RECEIPT;
	// Sending unreliably with an ack receipt requires the receipt number, and that you inform the system of ID_SND_RECEIPT_ACKED and ID_SND_RECEIPT_LOSS
	serializeParameters->pro[0].sendReceipt = replicaManager->GetRakPeerInterface()->IncrementNextSendReceipt();
	serializeParameters->messageTimestamp = RakNet::GetTime();
	_owner->StatusSerialize(&serializeParameters->outputBitstream[0]);
	return RakNet::RM3SR_SERIALIZED_ALWAYS_IDENTICALLY;
}
void SimpleNetworkObject::Deserialize(RakNet::DeserializeParameters *deserializeParameters) {
	_owner->StatusDeserialize(&deserializeParameters->serializationBitstream[0]);
}

void SimpleNetworkObject::OnPoppedConnection(RakNet::Connection_RM3 *droppedConnection)
{

}
void SimpleNetworkObject::NotifyReplicaOfMessageDeliveryStatus(RakNet::RakNetGUID guid, uint32_t receiptId, bool messageArrived)
{
	// When using UNRELIABLE_WITH_ACK_RECEIPT, the system tracks which variables were updated with which sends
	// So it is then necessary to inform the system of messages arriving or lost
}
