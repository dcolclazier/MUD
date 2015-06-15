#include "world.h"
#include "Status.h"
#include "utilities.h"
#include "command.h"

#include <fstream>
#include <string>

World* World::_instance = nullptr;
World::World()
{
	
	_database = Database::Instance();
	
	
	
	_events.register_event("PlayerLogin", new Event());
	_events.register_event("PlayerLogout", new Event());
	_events.register_event("InitComplete", new Event());

	_channels.add_channel("SYSTEM", RANK_ALL);
	_channels.add_channel("TEST", RANK_NONE);
	_channels.add_channel("ADMIN", RANK_ADMIN | RANK_GOD | RANK_BUILDER);
	_channels.add_channel("GLOBAL", RANK_ALL);
	_channels.add_channel("NEWBIE", RANK_ALL);

	_server = new Server(*this);
}

World::~World()
{
	delete _server;
}

bool World::ExecuteCommand(Player* player, std::string userInput)
{
	Command* command = nullptr;
	
	auto cmdList = _commands.get_commands();
	auto args = Parser::is_special(userInput) ? Parser::handle_special(userInput) : Parser::split(userInput);
	if (args.size() == 0) return false;
	auto verb = args[0];
	args.erase(args.begin());
	
	for (auto cmd : *cmdList)
	{
		if (cmd->name() == verb || cmd->contains_alias(verb))  {
			command = cmd;
		}
	}
	if (command == nullptr)
	{
		player->message("Pogj fharb rotsu? \r\n");
		return false;
	}
	if (!player->has_access(command))	{
		player->message("Pogj fharb rotsu?.\r\n");
		return false;
	}
	if (!player->can_execute(command))	{
		player->message("You can't do that while " + player->status().to_string() + ".\r\n");
		return false;
	}
	
	//should check player related abilities, race, etc
	command->Execute(player, verb, args);
	return true;
}

bool World::InitializeFiles()
{
	std::ifstream fin(LOGIN_BANNER);
	if (!fin) return false;  //TODO : LOG entry
	while (fin.peek() != std::ifstream::traits_type::eof())	{
		std::string line;
		getline(fin, line);
		_banner += line + "\r\n";
	} fin.close();


	return true;
}
