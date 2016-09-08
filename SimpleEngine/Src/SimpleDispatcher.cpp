#include "stdafx.h"
#include "SimpleDispatcher.h"

void SimpleDispatcher::AddListener(const SimpleEvent::DescriptorType& descriptor, EventCallback&& callback){

	_listeners[descriptor].push_back(callback);
}


void SimpleDispatcher::AddObjectListener(void* object, const SimpleEvent::DescriptorType& descriptor, EventCallback&& callback){

	_objectListeners[object][descriptor].push_back(callback);
}

void SimpleDispatcher::RemoveListener(const SimpleEvent::DescriptorType& descriptor, void *owner) {

	auto& listeners = _listeners[descriptor];

	auto it = listeners.begin();
	while (it != listeners.end()) {
		if ((*it) == owner) {
			listeners.erase(it);
			return;
		}
		++it;
	}

}


void SimpleDispatcher::RemoveObjectListener(void* object, const SimpleEvent::DescriptorType& descriptor, void *owner) {

	auto& listeners = _objectListeners[object][descriptor];
	auto it = listeners.begin();
	while (it != listeners.end()) {
		if ((*it) == owner) {
			listeners.erase(it);
			return;
		}
		++it;
	}
}

void SimpleDispatcher::RemoveAllObjectsListener(const SimpleEvent::DescriptorType& descriptor, void *owner) {

	for (auto o : _objectListeners) {
		auto& listeners = o.second[descriptor];
		auto it = listeners.begin();
		while (it != listeners.end()) {
			if ((*it) == owner) {
				listeners.erase(it);
				return;
			}
			++it;
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