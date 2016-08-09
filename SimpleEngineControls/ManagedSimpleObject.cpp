#include "Stdafx.h"
#include "ManagedSimpleObject.h"
#include "SimpleObject.h"

ManagedSimpleObject::ManagedSimpleObject()
{

}

ManagedSimpleObject::~ManagedSimpleObject()
{
	free(simpleObject);
}
