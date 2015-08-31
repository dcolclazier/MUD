#include "Event.h"
#include "EventContainer.h"


Event::Event() {
	_listeners = new std::vector<EventContainer*>();
}

Event::~Event() {
	for (auto listener : *_listeners) { delete listener; }
	delete _listeners;
}

void Event::invoke(EventArgs* args, void* trigger) {
	for (auto listener : *_listeners) {
		listener->action(args, trigger);
	}
}

unsigned int Event::add(const EVENTFUNC listener) {
	auto eventContainer = new EventContainer();
	_listenerCount++;
	eventContainer->action = listener;
	eventContainer->id = _listenerCount;
	_listeners->push_back(eventContainer);
	return eventContainer->id;
}

bool Event::remove(unsigned int id) {
	for (auto x = 0; x < _listeners->size(); ++x) {
		if ((*_listeners)[x]->id == id) {
			_listeners->erase(_listeners->begin() + x);
			return true;
		}
	}
	return false;
}