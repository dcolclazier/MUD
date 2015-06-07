#include "Player.h"

#include "World.h"
#include "Command.h"
#include "utilities.h"

void Player::set_password(std::string& password){
	_password = password;
}


Player::Player(SOCKET _serverSocket)
{
	_currentState = nullptr;
	_loggedIn = false;
	_userData = nullptr;
	_status = standing;
	_socket = new NormalSocket(_serverSocket, this);
	_playerRank = RANK_PLAYER;
}

Player::Player(NormalSocket* socket) : _socket(socket)
{
	_status = standing;
	_playerRank = RANK_PLAYER;
	
}

Player::~Player() {
	delete _socket;
	if(_currentState) delete _currentState;
}
void Player::switch_state(IUserState* newState)
{

	if (_currentState != nullptr)
		_currentState->deactivate();
	delete _currentState;

	_currentState = newState;

	if (newState) _currentState->activate();
}

bool Player::has_access(ISecure* secured) {
	return Utilities::bit_is_set(_playerRank, secured->get_access_level());
}
bool Player::can_execute(Command* command)
{
	return command->has_status(_status) ? true : false;
}



