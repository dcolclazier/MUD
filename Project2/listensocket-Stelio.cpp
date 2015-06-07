#include "ListenSocket.h"


int ListenSocket::read_socket(char* destination, int length)
{
	int bytes = recv(_socket, destination, length - 1, 0);
	if (bytes == SOCKET_ERROR)  {
		destination[0] = '\0';
		return bytes;
	}
	destination[bytes] = '\0';
	return bytes;
}
int ListenSocket::CreateSocket(HWND hWnd, UINT message, int port) {
	if (_status)
		return 0;

	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (!_socket)
		return 0;
	_address.sin_family = AF_INET;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = htonl(INADDR_ANY);
	if (!BindSocket())
		return 0;
	if (!MakeListenSocket(hWnd, message))
		return 0;
	_status = 1;

	return 1;
}
int ListenSocket::MakeListenSocket(HWND hWnd, UINT message) {
	if (listen(_socket, SOMAXCONN) == SOCKET_ERROR)
		return 0;
	if (WSAAsyncSelect(_socket, hWnd, message, (FD_ACCEPT | FD_READ | FD_CLOSE)) == SOCKET_ERROR)
		return 0;
	return 1;
}

ListenSocket::~ListenSocket()
{
	if (_status)
		CloseSocket();
}