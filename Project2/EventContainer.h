#pragma once
#include "EventArgs.h"
#include <functional>

typedef std::function<void(EventArgs*, void*)> EVENTFUNC;
class EventContainer {
public:
	EVENTFUNC action;
	unsigned int id;
};