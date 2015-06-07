#pragma once
#include "Socket.h"
#include <queue>
#include <string>

class NormalSocket;
class Player;

class InputHandle
{
protected:
	NormalSocket* _socket;
};


class NormalSocket : public Socket {

	std::queue<std::string> _commandQueue;

	char* _buffer;
	unsigned int _bufferSize;

	Player* _player;

	int read_socket(char* destination, int length) override;
	bool CreateSocket(SOCKET _serverSocket);
	bool CommandPending();

public:
	bool Read();
	std::string pop_command();
	std::string get_address();
	SOCKET sock() const { return _socket; }
	
	void push_command(const std::string& input);
	
	NormalSocket(SOCKET serverSocket, Player* player) : _player(player)
	{
		CreateSocket(serverSocket);
		_buffer = new char[MUD_LINE_MAX];
	}
	~NormalSocket();
protected:
	sockaddr_in _asyncaddr;
};