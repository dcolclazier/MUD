#include "world.h"
#include "commandmanager.h"
#include <iostream>


bool CommandManager::add_command(Command* cmd)
{
	if (exists(cmd)) return false;

	_commands.push_back(cmd);
	return true;
}

bool CommandManager::remove_command(Command* cmd)
{
	if (!exists(cmd)) return false;
	for (auto it = _commands.begin(); it < _commands.end(); ++it)	{
		if (*it == cmd) {
			_commands.erase(it);
			return true;
		}
	}
	return false;
}

bool CommandManager::exists(Command* cmd)
{
	for (auto command : _commands){
		if (command == cmd)return true;
	}
	return false;
}

bool CommandManager::list_commands(Command* cmd, Player* player)
{
	for (auto command : _commands)
	{
		player->message(command->name());
	}
	return true;
}