#pragma once
#include "SimpleConfiguration.h"
#include "SimpleReplicaManager.h"
#include "Events.h"

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

class SimpleNetworkObject; 
class SIMPLE_API SimpleNetworkManager{

public:

	bool Initialize();
	void Shutdown();
	bool InitServer(uint32_t port);
	bool InitClient(std::string ip, uint32_t port);
	void Replicate(SimpleNetworkObject* obj);
	void Sync(SimpleNetworkObject* obj, NetworkID id);
	void Advance(float dt);
	bool IsServer() { return _isServer; }

	enum EVENT_RECIPIENT {
		NONE,
		OWNER,
		OTHERS,
		OTHERS_BUT_OWNER,
		ALL
	};

	enum EVENT_TARGET {
		EVENT_SYSTEM,
		DIRECT_MESSAGE
	};

	void SendEvent(EVENT_RECIPIENT recipient, SimpleNetworkObject* sourceObject, SimpleNetworkObject* targetObject, NetworkMessageEvent& evt);
	void RelayMessage(EVENT_RECIPIENT recipient, EVENT_TARGET evtTarget, RakNet::RakNetGUID &source, RakNet::RakNetGUID &target, RakNet::NetworkID sourceObject, RakNet::RakString message);
	void SendDirectMessage(EVENT_RECIPIENT recipient, SimpleNetworkObject* sourceObject, SimpleNetworkObject* targetObject, NetworkMessageEvent& evt);
	RakNet::NetworkIDManager* GetNativeIDManager() { return _networkIDManager; }
protected:
		
	RakNet::RakPeerInterface* _rakPeer = nullptr;						// Purpose: UDP network communication
	RakNet::TeamManager* _teamManager = nullptr;						// Purpose: Sophisticated team management
	SimpleReplicaManager* _replicaManager = nullptr;				// Purpose: Game object replication
	RakNet::NetworkIDManager* _networkIDManager = nullptr;				// Purpose: Lookup game objects given ID. Used by ReplicaManager3
	RakNet::TCPInterface* _tcp = nullptr;								// Purpose: Connect to RakNet's hosted master server
	RakNet::NatPunchthroughClient* _natPunchthroughClient = nullptr; 	// Purpose: If UPNP fails, used to connect across routers.
	RakNet::NatTypeDetectionClient* _natTypeDetectionClient = nullptr;	// Purpose: Determine what type of router we are behind, if any
	RakNet::RPC4* _rpc4 = nullptr;										// Purpose: Used to call C functions on remote systems. Convenience function.
	RakNet::ReadyEvent* _readyEvent = nullptr;							// Purpose: Used for players to ready / unready in the lobby in a way that is properly synchronized under peer to peer
	RakNet::FullyConnectedMesh2* _fullyConnectedMesh2 = nullptr;		// Purpose: Automatically determine and migrate the host of a peer to peer session. Avoid partial connection failures when joining peer-to-peer games.
	RakNet::HTTPConnection2* _httpConnection2 = nullptr;				// Purpose: Helper class to parse http connection events
	
	bool _isServer = false;
	RakNet::SystemAddress _serverAddress;
	
};
