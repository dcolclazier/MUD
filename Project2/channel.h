#pragma once
#include "i_secure.h"
#include <vector>
class Player;

enum MessageType
{
	Info, Warning
};

class Channel : public ISecure
{
	FLAG _accessLevel;
	std::string _channelName;
	std::vector<Player*> _channelMembers;

public:
	Channel(std::string& name, FLAG access);
	void broadcast(std::string& message, MessageType type);
	void message_one(std::string& message, Player* player, MessageType type);
	void broadcast_all_but(std::string& message, MessageType type, Player* player);
	bool add_member(Player* player);
	bool contains_member(Player* player);
	bool remove_member(Player* player);
	bool remove_all_members();
	std::string get_name() const;
	void set_name(std::string name);
	void list_members(Player* requestor);
	FLAG get_access_level() const override;
	void set_access_level(FLAG accessLevel) override;
};