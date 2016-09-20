#pragma once
#include "SimpleConfiguration.h"

#define DEFAULT_SERVER_PORT 60000
#define MAX_CONNECTIONS 16
namespace RakNet {
	class RakPeerInterface;
	class TeamManager;
	class ReplicaManager3;
	class NetworkIDManager;
	class TCPInterface;
	class NatPunchthroughClient;
	class NatTypeDetectionClient;
	class RPC4;
	class ReadyEvent;
	class FullyConnectedMesh2;
	class HTTPConnection2;
}


class SIMPLE_API SimpleNetworkManager{

public:

	bool Initialize();
	void Shutdown();
	bool InitServer(uint32_t port);
	bool InitClient(std::string ip, uint32_t port);
	void Advance(float dt);
	
protected:
		
	RakNet::RakPeerInterface* _rakPeer;						// Purpose: UDP network communication
	RakNet::TeamManager* _teamManager;						// Purpose: Sophisticated team management
	RakNet::ReplicaManager3* _replicaManager3;				// Purpose: Game object replication
	RakNet::NetworkIDManager* _networkIDManager;			// Purpose: Lookup game objects given ID. Used by ReplicaManager3
	RakNet::TCPInterface* _tcp;								// Purpose: Connect to RakNet's hosted master server
	RakNet::NatPunchthroughClient* _natPunchthroughClient; 	// Purpose: If UPNP fails, used to connect across routers.
	RakNet::NatTypeDetectionClient* _natTypeDetectionClient;	// Purpose: Determine what type of router we are behind, if any
	RakNet::RPC4* _rpc4;										// Purpose: Used to call C functions on remote systems. Convenience function.
	RakNet::ReadyEvent* _readyEvent;							// Purpose: Used for players to ready / unready in the lobby in a way that is properly synchronized under peer to peer
	RakNet::FullyConnectedMesh2* _fullyConnectedMesh2;		// Purpose: Automatically determine and migrate the host of a peer to peer session. Avoid partial connection failures when joining peer-to-peer games.
	RakNet::HTTPConnection2* _httpConnection2;				// Purpose: Helper class to parse http connection events
	

	bool isServer = false;
};
