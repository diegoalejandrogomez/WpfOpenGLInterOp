#pragma once
#include "SimpleSerializable.h"
#include "SimpleNetworkObject.h"
#include "SimpleConfiguration.h"

class SIMPLE_API SimpleGameLogic : public SimpleSerializable, public SimpleNetworkSerializable {
public:

	virtual void Init() = 0;
	virtual void Advance(float dt) = 0;
	virtual void Shutdown() = 0;
	virtual bool IsRunning() = 0;
	
	//Network
	virtual uint32_t GetNetworkID() { return 1; }
	SimpleNetworkObject*_netObj;

protected:
	void InitNetwork() {
		_netObj = new SimpleNetworkObject();
		_netObj->SetOwner(this);
		_netObj->SetNetworkType(SimpleID("STATIC"));
		_netObj->Sync(GetNetworkID());
	}
};
