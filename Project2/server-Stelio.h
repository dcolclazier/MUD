#pragma once
#include "EventManager.h"
#include "ListenSocket.h"
#include <vector>
#include <map>
#include <string>
class World;
class LogManager;
class NormalSocket;
class Player;

class Server
{
	std::vector<std::string> _banList; //used
	std::map<SOCKET, Player*> _playerList; //a key-value pair list, client-side socket is key, Player object is value
		
	EventManager _events; //for adding and triggering events related to connect and disconnects.
	ListenSocket _listenSocket; //the socket on the server's end
	LogManager* _logger; // reference to World::logger
	World* _world; //reference to static world
public:

	Server(World* world);
	EventManager* events();
	void RemoveAllUsers();
	
	bool ip_banned(std::string ip_address);
	void process_new_connection(SOCKET socket);
	void process_disconnect(SOCKET socket);
	void handle_socketMessage(WPARAM wParam, LPARAM lParam);
	Player* get_player(SOCKET sock);

	~Server() {
		RemoveAllUsers();
		_listenSocket.CloseSocket();
	}
	int player_count();
	ListenSocket* socket() { return &_listenSocket; }
};