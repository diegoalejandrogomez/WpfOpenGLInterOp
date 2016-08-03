#pragma once

class SimpleEvent
{
public:
	typedef  const char* DescriptorType;
	virtual ~SimpleEvent(){};
	virtual DescriptorType type() const = 0;
};


