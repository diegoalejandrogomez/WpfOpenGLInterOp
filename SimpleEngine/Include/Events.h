#pragma once
#include "SimpleEvent.h"

class DebugEvent : public SimpleEvent
{
public:
	DebugEvent(void* source) : SimpleEvent(source) {};
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
	WindowResizeEvent(float w, float h):width(w), height(h), SimpleEvent(nullptr) {};
	virtual ~WindowResizeEvent() {};

	static constexpr DescriptorType descriptor = "WindowResizeEvent";

	virtual DescriptorType type() const
	{
		return descriptor;
	}

	float width;
	float height;
};


class SimpleCharacter;

class CharacterDiedEvent : public SimpleEvent
{
public:
	CharacterDiedEvent(void * source, SimpleCharacter* character) : SimpleEvent(source),  _character(character) {}
	virtual ~CharacterDiedEvent() {};

	static constexpr DescriptorType descriptor = "CharacterDiedEvent";

	virtual DescriptorType type() const
	{
		return descriptor;
	}
	SimpleCharacter* _character;
};


///GUI Events


class SimpleWindow;
class WindowClosed : public SimpleEvent
{
public:
	WindowClosed(void * source, SimpleWindow* window) : SimpleEvent(source), _window(window) {}
	virtual ~WindowClosed() {};

	static constexpr DescriptorType descriptor = "WindowClosed";

	virtual DescriptorType type() const
	{
		return descriptor;
	}
	SimpleWindow* _window;
};
