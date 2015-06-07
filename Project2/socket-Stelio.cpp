#include "Socket.h"
#include "Defines.h"
#include <string>


void Socket::Message(std::string message, std::string color) {
	auto msg = color + message + RESET;
	send(_socket, msg.c_str(), msg.length(), 0);
}


void Socket::CloseSocket()
{
	shutdown(_socket, 1);
	closesocket(_socket);
	_status = 0;

}

bool Socket::BindSocket()
{
	return bind(_socket, reinterpret_cast<LPSOCKADDR>(&_address), sizeof(_address)) != SOCKET_ERROR ? true : false;
}