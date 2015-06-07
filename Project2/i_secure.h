#pragma once
#include "utilities.h"

class Player;

class ISecure
{
public:
	virtual ~ISecure() {}
	virtual FLAG get_access_level() const = 0;
	virtual void set_access_level(FLAG accessLevel) = 0;
};