#include "stdafx.h"
#include "SimpleDispatcher.h"

void SimpleDispatcher::AddListener(const SimpleEvent::DescriptorType& descriptor, EventCallback&& callback){

	_listeners[descriptor].push_back(callback);
}

void SimpleDispatcher::RemoveListener(const SimpleEvent::DescriptorType& descriptor, void *owner) {

	auto& listeners = _listeners[descriptor];

	auto it = listeners.begin();
	while (it != listeners.end()) {
		if ((*it) == owner) {
			listeners.erase(it);
			return;
		}
	}

}


void SimpleDispatcher::Flush() {

	while (!_queuedEvents.empty()) {
		SimpleEvent *evt = _queuedEvents.front();

		if (_listeners.find(evt->type()) == _listeners.end())
			return;

		auto& listeners = _listeners.at(evt->type());

		for (auto& listener : listeners)
			listener(*evt);

		SIMPLE_LOG("Sent delayed event %s", evt->type());

		delete evt;
		_queuedEvents.pop();
	}

}