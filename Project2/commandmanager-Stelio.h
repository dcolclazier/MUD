#pragma once
#include <vector>
#include "command.h"

class CommandManager
{
	std::vector<Command*> _commands;
	
public:
	~CommandManager();
	bool add_command(Command* cmd);
	bool remove_command(Command* cmd);
	bool exists(Command* cmd);
	bool list_commands(Command* cmd, Player* player);
	std::vector<Command*>* get_commands() { return &_commands; }
};