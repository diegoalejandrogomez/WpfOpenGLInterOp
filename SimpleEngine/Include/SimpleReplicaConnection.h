#pragma once
#include <ReplicaManager3.h>
#include "SimpleID.h"

using namespace RakNet;

class SimpleReplicaConnection : public Connection_RM3 {
public:
	SimpleReplicaConnection(const SystemAddress &_systemAddress, RakNetGUID _guid) : Connection_RM3(_systemAddress, _guid) {}
	virtual ~SimpleReplicaConnection() {}

	// See documentation - Makes all messages between ID_REPLICA_MANAGER_DOWNLOAD_STARTED and ID_REPLICA_MANAGER_DOWNLOAD_COMPLETE arrive in one tick
	bool QueryGroupDownloadMessages(void) const { return true; }

	virtual Replica3 *AllocReplica(RakNet::BitStream *allocationId, ReplicaManager3 *replicaManager3);
protected:
};
