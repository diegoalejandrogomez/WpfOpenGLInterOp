#pragma once
#include "SimpleConfiguration.h"
#include "SimpleReplicaConnection.h"

class SIMPLE_API SimpleReplicaManager: public ReplicaManager3
{
	virtual Connection_RM3* AllocConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID) const {
		return new SimpleReplicaConnection(systemAddress, rakNetGUID);
	}
	virtual void DeallocConnection(Connection_RM3 *connection) const {
		delete connection;
	}
};

