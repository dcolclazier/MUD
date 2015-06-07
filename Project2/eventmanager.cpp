#include "EventManager.h"


bool EventManager::register_event(const std::string& name, Event* event)
{
	if (_events.count(name) > 0) return false;
	if (event == nullptr) return false;

	_events[name] = event;
	return true;
}

bool EventManager::event_registered(const std::string& name)
{
	return _events.count(name) == 0 ? false : true;
}

Event* EventManager::get_event(const std::string& name)
{
	if (!event_registered(name)) return false;
	return _events[name];
}

bool EventManager::remove_event(const std::string& name)
{
	return _events.erase(name) ? true : false;
}

bool EventManager::trigger_event(const std::string& name, EventArgs* args, void* caller)   {
	if (!event_registered(name))
		return false;
	_events[name]->invoke(args, caller);
	return true;
}

bool EventManager::add_listener(const std::string& name, const EVENTFUNC callBack)
{
	if (!event_registered(name))
		return false;
	_events[name]->add(callBack);
	return true;
}

Event::Event()
{
	_listeners = new std::vector<EventContainer*>();
}

Event::~Event()
{
	for (auto listener : *_listeners) 	{ delete listener; }
	delete _listeners;
}

void Event::invoke(EventArgs* args, void* trigger)
{
	for (auto listener : *_listeners)
	{
		listener->action(args, trigger);
	}
}

unsigned int Event::add(const EVENTFUNC listener)
{
	auto eventContainer = new EventContainer();
	_listenerCount++;
	eventContainer->action = listener;
	eventContainer->id = _listenerCount;
	_listeners->push_back(eventContainer);
	return eventContainer->id;
}

bool Event::remove(unsigned int id)
{
	for (auto x = 0; x < _listeners->size(); ++x)	{
		if ((*_listeners)[x]->id == id) {
			_listeners->erase(_listeners->begin() + x);
			return true;
		}
	}
	return false;
}