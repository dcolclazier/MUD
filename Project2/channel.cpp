#include "channel.h"
#include "player.h"


Channel::Channel(std::string& name, FLAG access) : _accessLevel(access), _channelName(name)
{
	_channelMembers.clear();
}

void Channel::broadcast(std::string& message, MessageType type)
{
	for (auto member : _channelMembers)	{ message_one(message, member, type); }
}
void Channel::message_one(std::string& message, Player* player, MessageType type)
{
	player->message(std::string(BOLDMAGENTA) +_channelName + RESET + ": " + message + "\r\n");
}

void Channel::broadcast_all_but(std::string& message, MessageType type, Player* playerToSkip)
{
	for (auto member : _channelMembers)
	{
		if (member != playerToSkip) message_one(message, member, type);
	}
}

bool Channel::add_member(Player* player)
{
	if (contains_member(player)) return false;
	_channelMembers.push_back(player);
	return true;
}

bool Channel::contains_member(Player* player)
{
	for (auto member : _channelMembers)	{
		if (member == player) return true;
	}
	return false;
}

bool Channel::remove_member(Player* player)
{
	if (!contains_member(player)) return false;
	for (auto i = _channelMembers.begin(); i < _channelMembers.end(); ++i)
	{
		if (*i == player) _channelMembers.erase(i);
		return true;
	}
	return false;
}

bool Channel::remove_all_members()
{
	while (_channelMembers.size() > 0)	{
		remove_member(*_channelMembers.begin());
	}
	return true;
}

std::string Channel::get_name() const
{
	return _channelName;
}

void Channel::set_name(std::string name)
{
	_channelName = name;
}

void Channel::list_members(Player* requestor)
{
	for (auto member : _channelMembers)
	{
		message_one(_channelName + " member: " + member->name(), requestor, Info);
		//requestor->Message(_channelName + " member: " + member->name());
	}
}

FLAG Channel::get_access_level() const
{
	return _accessLevel;
}

void Channel::set_access_level(FLAG accessLevel)
{
	_accessLevel = accessLevel;
}