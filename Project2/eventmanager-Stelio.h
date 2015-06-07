/*Any class (World, Network, Player, Object, etc) that needs to have events will also have an
event manager.

*/
#pragma once

#include <map>
#include <functional>
#include <vector>


class EventArgs {
public:
	virtual ~EventArgs() {}
};

typedef std::function<void(EventArgs*, void*)> EVENTFUNC;

class EventContainer
{
public:
	EVENTFUNC action;
	unsigned int id;
};
#define EVENT(name)\
	void name(EventArgs* args, void* caller)

class Event
{
	int _listenerCount;
	std::vector<EventContainer*>* _listeners;
	
public:
	Event();
	~Event();
	void invoke(EventArgs* args, void* trigger);
	unsigned int add(const EVENTFUNC listener);
	bool remove(unsigned id);
};



class EventManager
{
	std::map <std::string, Event*> _events;

public:
	EventManager() {}
	~EventManager() {
		for (auto event : _events) {
			delete event.second;
		}
	}

	bool register_event(const std::string& name, Event* event);
	bool event_registered(const std::string& name);
	Event* get_event(const std::string& name);
	bool remove_event(const std::string& name);
	
	bool trigger_event(const std::string& name, EventArgs* args, void* trigger);
	bool add_listener(const std::string& name, const EVENTFUNC listener);

	
};