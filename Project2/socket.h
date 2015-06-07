#pragma once
#include <windows.h>
#include "Defines.h"
#include <string>

//#include <winsock2.h>

class Socket {

	
public:
	virtual ~Socket()
	{
	}
	
	inline int GetStatus() const { return _status; }
	inline SOCKET GetSocket() const { return _socket; }

	//Send text to the socket
	void Message(std::string message, std::string color) {
		auto msg = color + message + RESET;
		send(_socket, msg.c_str(), msg.length(), 0);
	}

	virtual int GetText(char* destination, int length) = 0;

	void CloseSocket();

protected:
	int _status;		   //Connected?		
	SOCKET _socket;		   //Winsock representation of socket	
	SOCKADDR_IN _address;  //address of socket (IP & port)

	//binds the address to the socket
	int BindSocket();
};