#include "Stdafx.h"
#include "ManagedSimpleLayer.h"

ManagedSimpleLayer::ManagedSimpleLayer(SimpleLayer *simpleLayer) {
	this->simpleLayer = simpleLayer;
	_simpleObjects = gcnew System::Collections::Generic::List<ManagedSimpleObject^>();
	for (auto &entity : this->simpleLayer->GetEntities())
	{
		auto managedSimpleObject = gcnew ManagedSimpleObject();
		managedSimpleObject->SetSimpleObject(entity);
		_simpleObjects->Add(managedSimpleObject);
	}
};

ManagedSimpleLayer::~ManagedSimpleLayer()
{
};
