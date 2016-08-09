#include "Stdafx.h"
#include "ManagedSimpleObject.h"

ManagedSimpleObject::ManagedSimpleObject()
{

}

ManagedSimpleObject::~ManagedSimpleObject()
{
	free(simpleObject);
}
