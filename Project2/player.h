#pragma once
#include "NormalSocket.h"
#include "tinyxml.h"
#include "i_userstate.h"
#include "Status.h"
#include "eventmanager.h"

#include "parser.h"

//#include <deque>

class ISecure;
struct Statuss;
class World;

class Player  {


	//why not write a component system like the event system? The general idea would be
	//to have generic game objects, which then have a list of components turning them into whatever they are
	//for instance, a player would get a component containing their network name, socket info, etc, and a component containing their character information once they create one... Seems pretty versatile!

	//try to model it the same way - it will help you solidify what you know about how the event system works
	std::string _password;
	IUserState* _currentState;
	NormalSocket* _socket;
	TiXmlElement* _userData;
	FLAG _playerRank;
	Status _status;
	
	bool _loggedIn;

public:
	void set_password(std::string& password);
	const std::string& password() const { return _password; }
	void set_logged_in(bool in)	{ _loggedIn = in; }
	const bool& logged_in() const {return _loggedIn;}

	Status status() const { return _status; }
	void set_status(Status status) { _status = status; }
	explicit Player(SOCKET _serverSocket);
	explicit Player(NormalSocket* socket);
	~Player();

	void switch_state(IUserState* newState);
	bool has_access(ISecure* secured);
	
	void UserData(TiXmlElement* data) { _userData = data; }
	TiXmlElement* UserData() const { return _userData; }
	
	IUserState* current_state() const { return _currentState; }
	void current_state(IUserState* state) { _currentState = state; }


	bool can_execute(Command* command);

	NormalSocket* socket() const { return _socket; }

	void message(std::string& str, const char* color = RESET) { _socket->Message(str,color); }

	std::string name() const {
		if (!_userData) return "";
		return _userData->Attribute("name");
	}

};