#include "cmds_generic.h"
#include "utilities.h"
#include "world.h"
#include "player.h"
#include <string>
#include <vector>
#include <sstream>
void InitializeGenericCmds()
{
	auto world = World::world();

	world->commands()->add_command(new SayCommand());

}
//asdf
void SayCommand::Execute(Player* player, std::string& verb, std::vector<std::string>& args)
{
	if (args.size() <= 0) {
		player->message("Say what? \n");
		return;
	}
	std::stringstream sout;
	sout << BOLDMAGENTA << player->name() << RESET << ": " << Parser::join(args);

	////todo - replace with room code
	World::world()->channels()->message("GLOBAL", sout.str(), Info);
}

SayCommand::SayCommand()
{
	set_name("say");
	add_aliases({"sa"});

	set_access_level(RANK_PLAYER);
	add_status({ standing, sitting, resting });
}
