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
	std::vector<SOCKET> _connectedSockets;

	std::vector<std::string> _banList; //used
	std::map<SOCKET, Player*> _playerList; //used
		
	//std::vector<Player*> _userList;
	EventManager _events; //used
	ListenSocket _listenSocket; //used
	LogManager* _logger; //used
	World* _world; //used
public:

	Server(World* world);
	EventManager* events();
	void RemoveAllUsers();
	
	bool ip_banned(std::string ip_address);
	void process_new_connection(SOCKET socket);
	void process_disconnect(SOCKET socket);
	void SocketMessageHandler(WPARAM wParam, LPARAM lParam);
	Player* get_player(SOCKET sock);

	~Server() {
		RemoveAllUsers();
		_listenSocket.CloseSocket();
	}
	int player_count();
	ListenSocket* socket() { return &_listenSocket; }
};