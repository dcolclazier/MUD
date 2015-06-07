#include "NormalSocket.h"
#include "World.h"
//#include "Winsock2.h"
#include <sstream>
#include <string>

int NormalSocket::read_socket(char* data, int length)
{
	auto bytes = recv(_socket, data, length - 1, 0);
	if (bytes == SOCKET_ERROR) {
		data[0] = '\0';
		return 0;
	}
	data[bytes] = '\0';
	return bytes;
}

bool NormalSocket::Read()
{
	// Grab the text from the buffer and note the increase in size
	_bufferSize += read_socket(_buffer + _bufferSize, MUD_LINE_MAX - _bufferSize);

	// here we check if there are any return characters in the buffer, and if so, we execute that section of the buffer
	auto returnChar = strchr(_buffer, '\r');

	if (returnChar == nullptr || _bufferSize >= MUD_LINE_MAX - 1) {
		// If there is no enter character, but the buffer is full, it means there is a flood condition
		// We clear the buffer, because once this occurs, it is impossible for the player to press enter to execute the buffer
		delete[] _buffer;
		_buffer = new char[MUD_LINE_MAX];
		_bufferSize = 0;
		return false;
	}
	
	std::string execbuf;

	do {
		// Change the buffer so it has a null terminator at the enter point.
		// This basically chops everything off after the enter for the purposes of being a string.
		returnChar[0] = '\0';

		// Create a new buffer for the remainder of the text and fill it
		// Also checks for a newline character right after the carriage return character and removes it if necessary
		auto newbuffer = new char[MUD_LINE_MAX];
		memcpy(newbuffer, returnChar + ((returnChar[1] == '\n') ? 2 : 1), _bufferSize - (returnChar + ((returnChar[1] == '\n') ? 1 : 0) - _buffer));

		// We now have what we want to execute, let's do it!
		execbuf = _buffer;
		if (execbuf.size() > MUD_SPAM_MAX) {
			Message("Quit trying to spam - enter something legit.\r\n", BOLDRED);
			execbuf = " ";
		}
		else {
			push_command(execbuf);
			_player->current_state()->run();
		}
		
		// make sure the size of the buffer reflects the fact that we just took text out of it - reduce it in size
		_bufferSize -= returnChar + (returnChar[1] == '\n' ? 2 : 1) - _buffer;

		// After execution, delete the original buffer and set it to what's left(newBuffer)
		delete[] _buffer;
		_buffer = newbuffer;

	} while ((returnChar = strchr(_buffer, '\r')) != nullptr); // see if there are any more enters in the buffer
	

	return true;
}

bool NormalSocket::CreateSocket(SOCKET _serverSocket) {
	if (_status) // Don't create a socket if one already exists
		return false;

	int addrsize = sizeof(sockaddr_in);
	_socket = accept(_serverSocket, reinterpret_cast<struct sockaddr*>(&_asyncaddr), &addrsize);
	if (_socket == INVALID_SOCKET)
		return false;
	_status = true;

	return true;
}

bool NormalSocket::CommandPending()
{
	return(_commandQueue.size() > 0);
}

std::string NormalSocket::pop_command()
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

void NormalSocket::push_command(const std::string& input)
{
	_commandQueue.push(input);
}





NormalSocket::~NormalSocket()
{
	if (_status)
		CloseSocket();
	delete _buffer;
}
