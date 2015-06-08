#include "Server.h"
#include "UserStates.h"
#include <string>
#include "Player.h"
#include <sstream>
class Authenticated;



Server::Server(World* world) :_world(world)
{
	_logger = _world->logger();
	_events.register_event("DirtyDisconnect", new Event());
}

EventManager* Server::events() 
{
	return &_events;
}

void Server::RemoveAllUsers() {

	for (auto player : _playerList)  {
		delete player.second;
	}
}
void Server::SocketMessageHandler(WPARAM wParam, LPARAM lParam) {

	SOCKET socket = static_cast<SOCKET>(wParam);
	switch (WSAGETSELECTEVENT(lParam)) {

	case FD_ACCEPT:
		process_new_connection(socket);
		break;
	case FD_CLOSE:
		//This should handle link-dead situations, right?
		process_disconnect(socket);
		break;
	case FD_READ:
		auto player = get_player(socket);
		player->socket()->Read();

		break;
	}
}

bool Server::ip_banned(std::string ip_address)
{
	for (auto IP : _banList) {
		if (IP == ip_address) return true;
	}
	return false;
}

void Server::process_new_connection(SOCKET socket)
{
	//initialize player socket
	auto player = new Player(_listenSocket.GetSocket());
	auto ip_address = player->socket()->get_address();
	_logger->write("network", "Socket connected: " + ip_address);

	//check player socket against ban list
	if (ip_banned(ip_address)) {
		_logger->write("network", "Connection killed: " + ip_address + " is banned.");
		player->message("You have been banned. Disconnecting.\r\n", BOLDRED);
		closesocket(socket);
		return;
	}

	//player isn't banned - add to list of connected players
	_playerList[player->socket()->sock()] = player;
	
	//move connected player to login screen
	player->switch_state(new Connected(player));
}

void Server::process_disconnect(SOCKET socket) {

	auto player = _playerList[socket];

	if (player->logged_in()) {
		_world->logger()->write("network", "Dirty disconnect detected: " + player->socket()->get_address());
		_events.trigger_event("DirtyDisconnect", nullptr, static_cast<void*>(player));
		//move to link dead users - TODO
		_playerList.erase(socket);
	}
	else {
		_world->logger()->write("network", "Clean disconnect: " + player->socket()->get_address());
		_playerList.erase(socket);
	}
	delete player;
}

Player* Server::get_player(SOCKET sock) {
	if (_playerList.count(sock) == 0) return nullptr;
	return _playerList[sock];
}

int Server::player_count()
{
	if (_playerList.size() > 0)	return _playerList.size();
	return 0;
}
