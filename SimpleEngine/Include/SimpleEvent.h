#pragma once
#include "SimpleConfiguration.h"

class SIMPLE_API SimpleEvent
{
public:
	typedef  const char* DescriptorType;
	virtual ~SimpleEvent(){};
	virtual DescriptorType type() const = 0;
};


