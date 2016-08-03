#pragma once
#include "SimpleEvent.h"

class DebugEvent : public SimpleEvent
{
public:
	DebugEvent() {};
	virtual ~DebugEvent() {};

	static constexpr DescriptorType descriptor = "DebugEvent";

	virtual DescriptorType type() const
	{
		return descriptor;
	}
};



class WindowResizeEvent : public SimpleEvent
{
public:
	WindowResizeEvent(float w, float h):width(w), height(h) {};
	virtual ~WindowResizeEvent() {};

	static constexpr DescriptorType descriptor = "WindowResizeEvent";

	virtual DescriptorType type() const
	{
		return descriptor;
	}

	float width;
	float height;
};