#pragma once
#include "Defines.h"
#include "Server.h"
#include "Database.h"
#include "EventManager.h"
#include "commandmanager.h"
#include "channelmanager.h"
#include "LogManager.h"
#include "Player.h"
#include <string>
//#include "ZoneManager.h"

//This class should be responsible for managing collections of objects (users, zones etc) as well
//as holding references to manager objects. All core functions will be kept in this class ,and tasks delegated
//to other classes as needed for organizational purposes

class Player;

class World {

	static World* _instance;
	Server* _server;
	Database* _database;
	std::string _banner;
	int _uptimeHrs;
	int _uptimeMin;
	
	EventManager _events;
	CommandManager _commands;
	ChannelManager _channels;
	//ZoneManager _zones;
	LogManager _logs;


public:

	World();
	~World();
	void destroy() { delete _instance; }


	std::string* banner() {	return &_banner;}
	LogManager* logger() { return &_logs; }
	Server* server() const { return _server; }
	Database* database() { return _database; }
	EventManager* events() { return &_events; }
	CommandManager* commands() { return &_commands; }
	ChannelManager* channels() { return &_channels; }

	//ZoneManager* zones() { return &_zones; }

	static World* world() {
		if (_instance == nullptr) _instance = new World;
		return _instance;
	}
	
	

	bool ExecuteCommand(Player* player, std::string playerInput);

	bool InitializeFiles();
};


