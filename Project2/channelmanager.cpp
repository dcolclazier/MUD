#include "channelmanager.h"
#include "player.h"
#include "world.h"

bool ChannelManager::InitChannels() {
	
	auto serverEvents = World::world()->server()->events();
	auto world_events = World::world()->events();
	world_events->add_listener("PlayerLogin", std::bind(&ChannelManager::OnPlayerLogin, this,  std::placeholders::_1, std::placeholders::_2));
	world_events->add_listener("PlayerLogout", std::bind(&ChannelManager::OnPlayerLogout, this, std::placeholders::_1, std::placeholders::_2));
	serverEvents.add_listener("DirtyDisconnect", std::bind(&ChannelManager::OnDirtyDisconnect, this, std::placeholders::_1, std::placeholders::_2));
	return true;
}

EVENT(ChannelManager::OnPlayerLogin)
{
	//temp - should actually load list of channels from user preferences
	auto player = static_cast<Player*>(caller);
	join_channel("SYSTEM", player);
	join_channel("GLOBAL", player);
	join_channel("TEST", player);
	player->message(std::string("Successfully logged in.\r\n"), BOLDCYAN);
	message("GLOBAL", std::string(GREEN) + player->name() + RESET + " logged in.\r\n", Info);
}
EVENT(ChannelManager::OnPlayerLogout) //hidden variable caller - points to object that triggered event
{
	//temp  - should also save the list of channels to the user preferences... or maybe shouldn't even go here?
	auto player = static_cast<Player*>(caller);
	leave_channel("SYSTEM", player);
	leave_channel("GLOBAL", player);
	leave_channel("TEST", player);
	
}
EVENT(ChannelManager::OnDirtyDisconnect) {
	auto player = static_cast<Player*>(caller);
	leave_channel("SYSTEM", player);
	leave_channel("GLOBAL", player);
	leave_channel("TEST", player);

}

bool ChannelManager::message(const std::string& channelName, const std::string& message, MessageType type)
{
	if (!channel_exists(channelName)) return false;
	_channelList[channelName]->broadcast(message, type);
	return true;
}

bool ChannelManager::join_channel(const std::string& channelName, Player* playerToJoin)
{
	if (!channel_exists(channelName)) return false;
	auto channelToJoin = _channelList[channelName];
	
	if (channelToJoin->contains_member(playerToJoin)) return false;

	if (!playerToJoin->has_access(channelToJoin))
	{
		playerToJoin->message("You don't have access to join " + channelName + ".\r\n",BOLDMAGENTA);
		return false;
	}
	
	_channelList[channelName]->add_member(playerToJoin);
	playerToJoin->message("Successfully joined " + channelName + ".\r\n", BOLDCYAN);
	return true;
}
bool ChannelManager::leave_channel(const std::string& channelName, Player* leavingPlayer)
{
	if (!channel_exists(channelName)) return false;
	return _channelList[channelName]->remove_member(leavingPlayer);
}

bool ChannelManager::add_channel(const std::string& channelName, FLAG channelAccessLevel)
{
	if (channel_exists(channelName)) return false;

	_channelList[channelName] = new Channel(channelName, channelAccessLevel);
	return true;
}

bool ChannelManager::remove_channel(const std::string& channelName)
{
	if (!channel_exists(channelName)) return false;
	
	_channelList[channelName]->remove_all_members();

	auto channelToDelete = _channelList.find(channelName);
	_channelList.erase(channelToDelete);
	
	delete _channelList[channelName];
	return true;
}

bool ChannelManager::channel_exists(const std::string& channelName)
{
	return (_channelList.count(channelName) > 0);
}