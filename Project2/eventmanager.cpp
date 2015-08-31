#include "EventManager.h"

class Event;

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
	if (!event_registered(name)) return nullptr;
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


