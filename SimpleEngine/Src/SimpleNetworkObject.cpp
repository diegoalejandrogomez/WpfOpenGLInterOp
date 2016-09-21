#include "stdafx.h"
#include "SimpleEngine.h"


void SimpleNetworkObject::Replicate() {

	SimpleEngine::Instance()->GetNetwork()->Replicate(this);
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
void SimpleNetworkObject::DeallocReplica(RakNet::Connection_RM3 *sourceConnection) {
	delete this;
}

RakNet::RM3ConstructionState SimpleNetworkObject::QueryConstruction(RakNet::Connection_RM3 *destinationConnection, RakNet::ReplicaManager3 *replicaManager3) {
	SimpleNetworkManager* man = SimpleEngine::Instance()->GetNetwork();

	if (_authOwner == AUTH_LOCAL)
		return QueryConstruction_ClientConstruction(destinationConnection, SimpleEngine::Instance()->GetNetwork()->IsServer());
	else
		return QueryConstruction_ServerConstruction(destinationConnection, SimpleEngine::Instance()->GetNetwork()->IsServer());
}

bool SimpleNetworkObject::QueryRemoteConstruction(RakNet::Connection_RM3 *sourceConnection) {
	SimpleNetworkManager* man = SimpleEngine::Instance()->GetNetwork();
	if (_authOwner == AUTH_LOCAL)
		return QueryRemoteConstruction_ClientConstruction(sourceConnection, SimpleEngine::Instance()->GetNetwork()->IsServer());
	else
		return QueryRemoteConstruction_ServerConstruction(sourceConnection, SimpleEngine::Instance()->GetNetwork()->IsServer());
}

RakNet::RM3ActionOnPopConnection SimpleNetworkObject::QueryActionOnPopConnection(RakNet::Connection_RM3 *droppedConnection) const{
	if (SimpleEngine::Instance()->GetNetwork()->IsServer()) {
		return QueryActionOnPopConnection_Server(droppedConnection);
	}
	else {
		return QueryActionOnPopConnection_Client(droppedConnection);
	}

}

RakNet::RM3QuerySerializationResult SimpleNetworkObject::QuerySerialization(RakNet::Connection_RM3 *destinationConnection) {
	if (_authOwner == AUTH_LOCAL)
		return QuerySerialization_ClientSerializable(destinationConnection, SimpleEngine::Instance()->GetNetwork()->IsServer());
	else
		return QuerySerialization_ServerSerializable(destinationConnection, SimpleEngine::Instance()->GetNetwork()->IsServer());

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
