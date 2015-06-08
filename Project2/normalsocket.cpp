#include "NormalSocket.h"
#include "World.h"
//#include "Winsock2.h"
#include <sstream>

int NormalSocket::GetText(char* destination, int length)
{
	int bytes = recv(_socket, destination, length - 1, 0);
	if (bytes == SOCKET_ERROR) {
		destination[0] = '\0';
		return 0;
	}
	destination[bytes] = '\0';
	return bytes;
}
bool NormalSocket::Read()//YUCK YUCK - I HATE THIS FUNCTION.
{
	// Grab the text from the buffer and note the increase in size
	_bufferSize += GetText(_buffer + _bufferSize, MUD_LINE_MAX - _bufferSize);

	// here we check if there are any return characters in the buffer, and if so, we execute that section of the buffer
	char* returnChar = strchr(_buffer, '\r');

	if (returnChar == nullptr) {
		// If there is no enter character, but the buffer is full, it means there is a flood condition
		// We clear the buffer, because once this occurs, it is impossible for the player to use enter to execute the buffer
		if (_bufferSize >= MUD_LINE_MAX - 1) {
			delete[] _buffer;
			_buffer = new char[MUD_LINE_MAX];
			_bufferSize = 0;
			return false;
		}
	}
	else {
		std::string execbuf;

		do {
			// Change the buffer so it has a null terminator at the enter point.
			// This basically chops everything off after the enter for the purposes of being a string.
			returnChar[0] = '\0';

			// Create a new buffer for the remainder of the text and fill it
			// Also checks for a newline character right after the carriage return character and removes it if necessary
			char* newbuffer = new char[MUD_LINE_MAX];
			memcpy(newbuffer, returnChar + ((returnChar[1] == '\n') ? 2 : 1), _bufferSize - (returnChar + ((returnChar[1] == '\n') ? 1 : 0) - _buffer));

			// We now have what we want to execute, let's do it!
			execbuf = _buffer;
			//Execute(execbuf);

			if (execbuf.size() > MUD_SPAM_MAX) {
				Message("Quit trying to spam - enter something legit.\r\n", BOLDRED);
				execbuf = " ";
			}
			else {
				_commandQueue.push(execbuf);
				_player->current_state()->run();
			}
			// Our new buffer will have a new size
			_bufferSize -= returnChar + (returnChar[1] == '\n' ? 2 : 1) - _buffer;

			// After execution, delete the original buffer
			delete[] _buffer;

			// and set it to the new buffer
			_buffer = newbuffer;

		} while ((returnChar = strchr(_buffer, '\r')) != nullptr); // see if there are any more enters in the buffer
	}

	return true;
}

int NormalSocket::CreateSocket(HWND hWnd, UINT message, int port) {
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
	if (hWnd)
		if (WSAAsyncSelect(_socket, hWnd, message, (FD_READ | FD_CLOSE)) == SOCKET_ERROR)
			return 0;
	_status = 1;

	return 1;
}

bool NormalSocket::CommandPending()
{
	return(_commandQueue.size() > 0);
}

std::string NormalSocket::PopCommand()
{
	if (!CommandPending()) return "";

	auto command = _commandQueue.front();
	_commandQueue.pop();
	return command;
}

std::string NormalSocket::get_address()
{
	return inet_ntoa(_asyncaddr.sin_addr);
}

void NormalSocket::AddCommand(const std::string& input)
{
	_commandQueue.push(input);
}

int NormalSocket::CreateSocket(SOCKET _serverSocket) // bool, please?
{
	if (_status) // Don't create a socket if one already exists
		return 0;

	int addrsize = sizeof(sockaddr_in);
	_socket = accept(_serverSocket, (struct sockaddr*)&_asyncaddr, &addrsize);
	if (_socket == INVALID_SOCKET)
		return 0;
	_status = 1;

	return 1;
}



NormalSocket::~NormalSocket()
{
	if (_status)
		CloseSocket();
}
