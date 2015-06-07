#include "Command.h"
#include "cmds_generic.h"

class Player;
bool InitializeCommands();

std::string& Command::name(){ return _name; }

void Command::set_name(std::string val){ _name = val; }

void Command::add_alias(std::string alias){ _aliases.push_back(alias); }

void Command::add_aliases(std::vector<std::string> aliases)
{
	for (auto a : aliases)	{
		_aliases.push_back(a);
	}
}

bool Command::contains_alias(std::string& alias)
{
	for (auto a : _aliases)	{
		if(a == alias) return true;
	}
	return false;
}

void Command::add_status(Status status) { _validStatus.push_back(status); }

void Command::add_status(std::vector<Status> status)
{
	for (auto st : status)  {
		_validStatus.push_back(st);
	}
}

bool Command::has_status(Status status)
{
	for (auto st : _validStatus){
		if (st == status || st == any) return true;
	}
	return false;
}

void Command::set_access_level(FLAG access) { _access = access; }

FLAG Command::get_access_level() const { return _access; }

void Command::Execute(Player* player, std::string& verb, std::vector<std::string>& args)
{
}
bool InitializeCommands() {

	InitializeGenericCmds();
	return true;
}
