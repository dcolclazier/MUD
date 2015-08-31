#pragma once
#include <vector>
#include "EventContainer.h"

class Event {
	int _listenerCount;
	std::vector<EventContainer*>* _listeners;

public:
	Event();
	~Event();
	void invoke(EventArgs* args, void* trigger);
	unsigned int add(const EVENTFUNC listener);
	bool remove(unsigned id);
};
