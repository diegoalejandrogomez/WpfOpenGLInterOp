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


void SimpleDispatcher::_DispatchEvent(SimpleEvent *evt) const {

	//Try to call listeners of events with source
	if (evt->Source() != nullptr) {

		if (_objectListeners.find(evt->Source()) != _objectListeners.end()) {
			auto& object = _objectListeners.at(evt->Source());

			if (object.find(evt->type()) != object.end()) {
				auto& listeners = object.at(evt->type());
				for (auto& listener : listeners)
					listener(*evt);
			}
		}
	}

	//Now call the anonymous events
	if (_listeners.find(evt->type()) != _listeners.end()) {


		auto& listeners = _listeners.at(evt->type());

		for (auto& listener : listeners)
			listener(*evt);

		SIMPLE_LOG("Sent delayed event %s", evt->type());
	}

	delete evt;


}

void SimpleDispatcher::Flush() {

	while (!_queuedEvents.empty()) {
		SimpleEvent *evt = _queuedEvents.front();
		_DispatchEvent(evt);
		_queuedEvents.pop();
	
	}

}