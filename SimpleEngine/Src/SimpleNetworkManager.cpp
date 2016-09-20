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

bool SimpleNetworkManager::Initialize() {

	return true;
}


bool SimpleNetworkManager::InitServer(uint32_t port) {

	_rakPeer = RakNet::RakPeerInterface::GetInstance();
	if (port < 1024 || port > 65535)
		port = DEFAULT_SERVER_PORT;

	RakNet::SocketDescriptor sd(port, 0);
	_rakPeer->Startup(MAX_CONNECTIONS, &sd, 1);
	isServer = true;

	SIMPLE_LOG("Starting Server on port %d", port);
	_rakPeer->SetMaximumIncomingConnections(MAX_CONNECTIONS);

	return true;
}

bool SimpleNetworkManager::InitClient(std::string ip, uint32_t port){

	_rakPeer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd;
	_rakPeer->Startup(1, &sd, 1);
	isServer = false;
	if (port < 1024 || port > 65535)
		port = DEFAULT_SERVER_PORT;


	SIMPLE_LOG("Starting client");
	uint32_t tries = 12U;
	uint32_t msPerTry = 500U;
	RakNet::ConnectionAttemptResult result = _rakPeer->Connect(ip.c_str(), port, NULL, 0, NULL, 0, tries, msPerTry, 0);

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

void SimpleNetworkManager::Advance(float dt) {


}