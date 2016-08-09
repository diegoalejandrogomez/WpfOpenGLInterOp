#include "Stdafx.h"
#include "ManagedSimpleObject.h"

ManagedSimpleObject::ManagedSimpleObject()
{
}

ManagedSimpleObject::~ManagedSimpleObject()
{
	free(simpleObject);
}

void ManagedSimpleObject::SetPosition(glm::vec3& pos)
{
	this->simpleObject->SetPosition(pos);
}

void ManagedSimpleObject::SetSize(glm::vec2& size)
{
	this->simpleObject->SetSize(size);
}

void ManagedSimpleObject::SetOrientation(float orientation)
{
	this->simpleObject->SetOrientation(orientation);
}


glm::vec2 ManagedSimpleObject::GetSize()
{
	return this->simpleObject->GetSize();
}

