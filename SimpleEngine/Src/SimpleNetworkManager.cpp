#include "stdafx.h"
#include "SimpleNetworkManager.h"
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <FullyConnectedMesh2.h>
#include <TeamManager.h>
#include <Kbhit.h>
#include <RakSleep.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include <SocketLayer.h>
#include <ReplicaManager3.h>
#include <NetworkIDManager.h>
#include <NatPunchthroughClient.h>
#include <NatTypeDetectionClient.h>
#include <TCPInterface.h>
#include <ReadyEvent.h>
#include <PacketLogger.h>
#include <RPC4Plugin.h>
#include <HTTPConnection2.h>
#include "SimpleNetworkObject.h"
#include "SimpleDispatcher.h"
#include "Events.h"
#include "SimpleEngine.h"

bool SimpleNetworkManager::Initialize() {

	_networkIDManager = new RakNet::NetworkIDManager();
	_replicaManager = new SimpleReplicaManager();
	_replicaManager->SetNetworkIDManager(_networkIDManager);
	_rpc4 = RPC4::GetInstance();

	_rpc4->RegisterSlot("Event", [](RakNet::BitStream* userData, RakNet::Packet* packet) {
		
		SimpleNetworkManager* network = SimpleEngine::Instance()->GetNetwork();
		EVENT_RECIPIENT recipient;
		EVENT_TARGET evtTarget;
		uint32_t r;
		userData->Read<uint32_t>(r);
		recipient = (EVENT_RECIPIENT)r;
		userData->Read<uint32_t>(r);
		evtTarget = (EVENT_TARGET)r;

		RakNet::RakNetGUID source;
		RakNet::RakNetGUID target;
		userData->Read(source);
		userData->Read(target);
		NetworkID nID;
		userData->Read(nID);	
		RakNet::RakString msg;
		userData->Read(msg);

		if (recipient == NONE) {
			SimpleNetworkObject* sourceObject = network->GetNativeIDManager()->GET_OBJECT_FROM_ID<SimpleNetworkObject*>(nID);

			if (evtTarget == EVENT_SYSTEM) {
				SIMPLE_LOG("Received Event from GUID:%s : %s", source.ToString(), msg.C_String());
				SimpleDispatcher::Instance()->Send<NetworkMessageEvent>(sourceObject, std::string(msg.C_String()));
			}
			else {
				sourceObject->GetOwner()->NetworkMessageReceived(NetworkMessageEvent{ nullptr, msg.C_String() });
			}
		}
		else {
			network->RelayMessage(recipient,evtTarget ,source, target, nID, msg);		
		}
	},
	0);

	return true;
		
}

void SimpleNetworkManager::RelayMessage(EVENT_RECIPIENT recipient, EVENT_TARGET evtTarget, RakNet::RakNetGUID &source, RakNet::RakNetGUID &target, RakNet::NetworkID sourceObject, RakNet::RakString message) {

	

	if (IsServer()) {

		RakNet::BitStream stream;
		stream.Write<uint32_t>(EVENT_RECIPIENT::NONE); //Stop relay chain
		stream.Write<uint32_t>(evtTarget); 
		stream.Write(source);
		stream.Write(target);
		stream.Write(sourceObject);
		stream.Write(message);
		switch (recipient) {
		case OWNER:
			SIMPLE_LOG("Relaying Event from GUID:%s to Owner with GUID:%s : %s", source.ToString(), target.ToString(), message.C_String());
			_rpc4->Signal("Event", &stream, PacketPriority::IMMEDIATE_PRIORITY, PacketReliability::RELIABLE_ORDERED_WITH_ACK_RECEIPT, 0, target, false, false);
			break;
		case OTHERS:
			SIMPLE_LOG("Relaying Event from GUID:%s to Others with GUID:%s : %s", source.ToString(), target.ToString(), message.C_String());
			_rpc4->Signal("Event", &stream, PacketPriority::IMMEDIATE_PRIORITY, PacketReliability::RELIABLE_ORDERED_WITH_ACK_RECEIPT, 0, source, true, false);
			break;
		case OTHERS_BUT_OWNER:
			SIMPLE_LOG("Relaying Event from GUID:%s to Others but Owner with GUID:%s : %s", source.ToString(), target.ToString(), message.C_String());
			_rpc4->Signal("Event", &stream, PacketPriority::IMMEDIATE_PRIORITY, PacketReliability::RELIABLE_ORDERED_WITH_ACK_RECEIPT, 0, target, true, false);
			break;
		case ALL:
			SIMPLE_LOG("Relaying Event from GUID:%s to All with GUID:%s : %s", source.ToString(), target.ToString(), message.C_String());
			_rpc4->Signal("Event", &stream, PacketPriority::IMMEDIATE_PRIORITY, PacketReliability::RELIABLE_ORDERED_WITH_ACK_RECEIPT, 0, _rakPeer->GetMyGUID(), true, true);
			break;
		}
	
	}
	else {
		//If we are a client, send the message to the server, in order for it to be relayed
		RakNet::BitStream stream;
		stream.Write<uint32_t>(recipient);
		stream.Write<uint32_t>(evtTarget);
		stream.Write(source);
		stream.Write(target);
		stream.Write(sourceObject);
		stream.Write(message);
		SIMPLE_LOG("Sending Event to server for relaying with GUID:%s : %s", source.ToString(), message.C_String());
		_rpc4->Signal("Event", &stream, PacketPriority::IMMEDIATE_PRIORITY, PacketReliability::RELIABLE_ORDERED_WITH_ACK_RECEIPT, 0, _serverAddress , false, false);
	}


}

void SimpleNetworkManager::SendDirectMessage(EVENT_RECIPIENT recipient, SimpleNetworkObject* sourceObject, SimpleNetworkObject* targetObject, NetworkMessageEvent& evt) {
		
	//We can only send events from objects we own, unless we are server
	SIMPLE_ASSERT(sourceObject->IsLocal() || IsServer());
	
	RelayMessage(recipient, DIRECT_MESSAGE, sourceObject->GetCreatingSystemGUID(), targetObject->GetCreatingSystemGUID(), targetObject->GetNetworkID(), evt.message.c_str());

}
void SimpleNetworkManager::SendEvent(EVENT_RECIPIENT recipient, SimpleNetworkObject* sourceObject,SimpleNetworkObject* targetObject, NetworkMessageEvent& evt) {
	
	//We can only send events from objects we own, unless we are server
	SIMPLE_ASSERT(sourceObject == nullptr || sourceObject->IsLocal() || IsServer());

	RakNet::RakNetGUID sourceGUID = sourceObject == nullptr ? _rakPeer->GetMyGUID() : sourceObject->GetCreatingSystemGUID();
	RakNet::RakNetGUID targetGUID = targetObject == nullptr ? _rakPeer->GetGuidFromSystemAddress(UNASSIGNED_SYSTEM_ADDRESS) : targetObject->GetCreatingSystemGUID();
	RakNet::NetworkID nID = sourceObject == nullptr ? NetworkID() : sourceObject->GetNetworkID();
	RelayMessage(recipient,EVENT_SYSTEM ,sourceGUID, targetGUID, nID, evt.message.c_str());
}

void SimpleNetworkManager::Replicate(SimpleNetworkObject* obj) {
	_replicaManager->Reference(obj);
}

void SimpleNetworkManager::Sync(SimpleNetworkObject* obj, NetworkID id) {
	obj->SetNetworkIDManager(_networkIDManager);
	obj->SetNetworkID(id);
	_replicaManager->Reference(obj);
}

bool SimpleNetworkManager::InitServer(uint32_t port) {

	_rakPeer = RakNet::RakPeerInterface::GetInstance();
	if (port < 1024 || port > 65535)
		port = DEFAULT_SERVER_PORT;

	RakNet::SocketDescriptor sd(port, 0);
	_rakPeer->Startup(MAX_CONNECTIONS, &sd, 1);
	_isServer = true;

	SIMPLE_LOG("Starting Server on port %d", port);
	SIMPLE_LOG("Network GUID:%s", _rakPeer->GetMyGUID().ToString());
	_rakPeer->SetMaximumIncomingConnections(MAX_CONNECTIONS);

	_rakPeer->AttachPlugin(_replicaManager);
	_rakPeer->AttachPlugin(_rpc4);

	return true;
}

bool SimpleNetworkManager::InitClient(std::string ip, uint32_t port){

	_rakPeer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd;
	_rakPeer->Startup(1, &sd, 1);
	_isServer = false;
	

	if (port < 1024 || port > 65535)
		port = DEFAULT_SERVER_PORT;

	_serverAddress.FromStringExplicitPort(ip.c_str(),port) ;

	SIMPLE_LOG("Starting client");
	SIMPLE_LOG("Network GUID:%s", _rakPeer->GetMyGUID().ToString());
	uint32_t tries = 12U;
	uint32_t msPerTry = 500U;
	RakNet::ConnectionAttemptResult result = _rakPeer->Connect(ip.c_str(), port, NULL, 0, NULL, 0, tries, msPerTry, 0);
	_rakPeer->AttachPlugin(_replicaManager);
	_rakPeer->AttachPlugin(_rpc4);

	switch (result)
	{
		case RakNet::CONNECTION_ATTEMPT_STARTED:
			SIMPLE_LOG("Starting client... Connecting to ip %s:%d", ip.c_str(), port);
			
			return true;
		break;
	case RakNet::INVALID_PARAMETER:
			SIMPLE_LOG("Connection attempt failed to start: Invalid parameter");
			return false;
		break;
	case RakNet::CANNOT_RESOLVE_DOMAIN_NAME:
			SIMPLE_LOG("Connection attempt failed to start: Cannot resolve domain name");
			return false;
		break;
	case RakNet::ALREADY_CONNECTED_TO_ENDPOINT:
			SIMPLE_LOG("Connection attempt failed to start: Already connected");
			return false;
		break;
	case RakNet::CONNECTION_ATTEMPT_ALREADY_IN_PROGRESS:
			SIMPLE_LOG("Connection attempt failed to start: Already attemping...");
			return false;
		break;
	case RakNet::SECURITY_INITIALIZATION_FAILED:
			SIMPLE_LOG("Connection attempt failed to start: Security could not be initialized");
			return false;
		break;
	}


	return true;
}

void SimpleNetworkManager::Shutdown() {

	if (_rakPeer == nullptr)
		return;

	_rakPeer->Shutdown(500, 0, LOW_PRIORITY);
	RakNet::RakPeerInterface::DestroyInstance(_rakPeer);
	_rakPeer= nullptr;
	
}

//We should probably run this on another thread... someday
void SimpleNetworkManager::Advance(float dt) {
	
	if (!_rakPeer) return;

	RakNet::Packet *packet = nullptr;

	for (packet = _rakPeer->Receive(); packet; _rakPeer->DeallocatePacket(packet), packet = _rakPeer->Receive())
	{
		switch (packet->data[0])
		{
		case ID_NEW_INCOMING_CONNECTION:
			SIMPLE_LOG("A remote system has successfully connected");
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			SIMPLE_LOG("A remote system has disconnected");
			break;
		case ID_CONNECTION_LOST:
			SIMPLE_LOG("A remote system lost the connection");
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			SIMPLE_LOG("The connection to the server has been accepted");
			break;
		}
	}
}