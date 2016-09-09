#pragma once
#include "SimpleConfiguration.h"

class SIMPLE_API SimpleEvent
{
	void* _source = nullptr;
public:
	typedef  const char* DescriptorType;
	SimpleEvent(void* source) : _source(source) {};
		
	virtual ~SimpleEvent(){};
		virtual DescriptorType type() const = 0;
	
	void* Source() const { return _source; }
	
};


