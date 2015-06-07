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

//This class should be responsible for managing collections of objects (users, zones etc) as well
//as holding references to manager objects. All core functions will be kept in this class ,and tasks delegated
//to other classes as needed for organizational purposes

class Player;

class World {

	static World* _instance;   //initial day
	Server* _server;			//initial day
	Database* _database;
	std::string _banner;
	int _uptimeHrs;
	int _uptimeMin;
	
	EventManager _events;
	CommandManager _commands;
	ChannelManager _channels;
	LogManager _logs; //initial day


public:

	World();								//initial day
	~World();								//initial day
	void destroy() { delete _instance; }	//initial day


	std::string* banner() {	return &_banner;}
	LogManager* logger() { return &_logs; }
	Server* server() const { return _server; } //initial day
	Database* database() { return _database; }
	EventManager* events() { return &_events; }
	CommandManager* commands() { return &_commands; }
	ChannelManager* channels() { return &_channels; }

	static World* world() { //initial day
		if (_instance == nullptr) _instance = new World;
		return _instance;
	}
	
	

	bool ExecuteCommand(Player* player, std::string playerInput);

	bool InitializeFiles();
};


