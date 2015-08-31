/*Any class (World, Network, Player, Object, etc) that needs to have events will also have an
event manager.

*/
#pragma once

#include <map>
#include "EventArgs.h"
#include "EventContainer.h"
#include "Event.h"




class EventManager
{
	std::map <std::string, Event*> _events;

public:
	EventManager() {}
	~EventManager() {}

	bool register_event(const std::string& name, Event* event);
	bool event_registered(const std::string& name);
	Event* get_event(const std::string& name);
	bool remove_event(const std::string& name);
	
	bool trigger_event(const std::string& name, EventArgs* args, void* trigger);
	bool add_listener(const std::string& name, const EVENTFUNC listener);

	
};