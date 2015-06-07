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
	Player* _player;

public:
	int GetText(char* destination, int length) override;
	bool Read();
	int CreateSocket(SOCKET _serverSocket);
	int CreateSocket(HWND hWnd, UINT message, int port);
	bool CommandPending();
	std::string PopCommand();
	std::string get_address();
	std::string get_host();
	void AddCommand(const std::string& input);
	SOCKET sock() const { return _socket; }
	unsigned int _bufferSize;
	char* _buffer;
	~NormalSocket();
	NormalSocket(SOCKET serverSocket, Player* player) : _player(player)
	{
		CreateSocket(serverSocket);
		_buffer = new char[MUD_LINE_MAX];
	}
protected:
	sockaddr_in _asyncaddr;
};