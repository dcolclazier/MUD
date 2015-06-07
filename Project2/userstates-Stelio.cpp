#include "UserStates.h"
#include "World.h"
#include "Server.h"
#include "Player.h"
#include  <fstream>
class CreateUserState;
class LoginState;

void Connected::deactivate() {

	//_player = nullptr;
}

void Connected::activate() {

	_player->message(*_world->banner());
	_player->message(std::string("\r\n\r\nBy what name do you wish to be known?\r\n\r\n -> "));
}

void Connected::run() {

	auto input = _player->socket()->pop_command();
		
	//if player data exists for username, grab and move to login state
	auto userData = _world->database()->GrabUserByName(input);
	if (userData != nullptr) {
		_player->UserData(userData);
		_player->switch_state(new LoginState(_player, 0));
		return;
	}
	else {//If player data doesn't exist, send name to NoPlayerFound state
		_player->switch_state(new PlayerNotFound(_player, input));
		return;
	}
	
}


void LoginState::deactivate() {
	
}

void LoginState::activate() {
	_player->message("\r\nEnter Password: ");
}

void LoginState::run() {
	auto input = _player->socket()->pop_command();
	//if the password was wrong, deal with it.
	if (input != _player->UserData()->Attribute("pass")) {
		_failedAttempts++;
		if (_failedAttempts >= 3) {
			_player->switch_state(new Connected(_player));
			return;
		}
		_player->message("Password does not match - try again...\r\n");
		_player->switch_state(new LoginState(_player, _failedAttempts));
		return;
	}

	//if the password was right, move to authenticated state.
	if (input == _player->UserData()->Attribute("pass")) {
		_player->switch_state(new Authenticated(_player));
		return;
	}



}
CreateUserState::CreateUserState(Player* player, std::string userName) {
	_player = player;
	_userName = userName;
	_world = World::world();
}

void CreateUserState::deactivate() {
	_player->message("Account Created! Logged In!\r\n");
	_world->channels()->message("NEWBIE", "Please welcome the new player, " + _player->name() + ", to the server!\r\n", Info);
}

void CreateUserState::activate() {
	_player->message("Creating...\r\nEnter Password: ");
	_userData = new TiXmlElement("player");
	_userData->SetAttribute("name", _userName.c_str());
}

void CreateUserState::run() {
	auto input = _player->socket()->pop_command();
	if (!_confirming) {
		if (input.size() < 6 || input.size() > 24) {
			_player->message("Password should be between 7 and 24 characters in length", BOLDRED);
			return;
		}
		_userData->SetAttribute("pass", input.c_str());
		_player->set_password(input);
		_player->message("Confirm Password: ");
		_confirming = true;
		return;
	}
	if (_confirming && input == _player->password()) {
		Database::Instance()->UserListElement->LinkEndChild(_userData);
		_player->UserData(_userData);
		_world->logger()->write("world", "player created: " + _player->name() + " : " + _player->socket()->get_address());
		_player->switch_state(new Authenticated(_player));
	}
	else  {
		_player->message("Password does not match. Please try again.", BOLDRED);
		return;
	}
}



void Authenticated::deactivate() {
	_player->set_logged_in(false);
	World::world()->events()->trigger_event("PlayerLogout", nullptr, _player);
}

void Authenticated::activate() {
	_player->set_logged_in(true);
	World::world()->events()->trigger_event("PlayerLogin", nullptr, _player);

}

void Authenticated::run() {
	auto input = _player->socket()->pop_command();
	World::world()->ExecuteCommand(_player, input);
}


void PlayerNotFound::deactivate()
{
}

void PlayerNotFound::activate()
{
	_player->message("That username does not exist. Would you like to create? ", BOLDBLUE);
}

void PlayerNotFound::run()
{
	auto input = _player->socket()->pop_command();

	if (input == "yes" || input == "y") {
		_player->switch_state(new CreateUserState(_player, _chosenName));
	}
	else _player->switch_state(new Connected(_player));
}