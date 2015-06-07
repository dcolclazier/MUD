#pragma once
#include <windows.h>
#include "Defines.h"
#include <string>

class Socket {

	
public:
	virtual ~Socket() { }
	
	inline bool GetStatus() const { return _status; }
	inline SOCKET GetSocket() const { return _socket; }
	
	//Send text to the socket
	void Message(std::string message, std::string color);

	//for base class implementation
	virtual int read_socket(char* data, int length) = 0;

	void CloseSocket();

protected:
	bool _status;		   //Connected?		
	SOCKET _socket;		   //Winsock representation of socket	
	SOCKADDR_IN _address;  //address of socket (IP & port)

	//binds the address to the socket
	bool BindSocket();
};