#pragma once
#include <string>

class IUserState{
	
public:
	virtual ~IUserState() = 0;
	virtual void deactivate() = 0;
	virtual void activate() = 0;
	virtual void run() = 0;
	//virtual void run(std::string& userInput);
};

inline IUserState::~IUserState()
{
}

