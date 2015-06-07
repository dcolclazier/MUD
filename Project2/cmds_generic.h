#pragma once;
#include <string>
#include <vector>
#include "Command.h"

class Player;
void InitializeGenericCmds();

class SayCommand : public Command {
public:
	SayCommand();
	void Execute(Player* player, std::string& verb, std::vector<std::string>& args) override;

};