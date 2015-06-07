#pragma once

#include "Socket.h"

class ListenSocket : public Socket  {
public:
	int GetText(char* destination, int length) override;
	int CreateSocket(HWND hWnd, UINT message, int port);
	int MakeListenSocket(HWND hWnd, UINT message);
	~ListenSocket();
};