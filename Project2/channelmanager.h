#pragma once

#include <map>
#include "channel.h"
#include "eventmanager.h"

class ChannelManager  {

	std::map<std::string, Channel*> _channelList;

public:
	bool InitChannels();
	bool join_channel(std::string channelName, Player* playerToJoin);
	bool leave_channel(std::string channelName, Player* playerToJoin);
	bool add_channel(std::string channelName, FLAG channelAccessLevel);
	bool remove_channel(std::string channelName);
	bool channel_exists(std::string channelName);
	
	EVENT(OnDirtyDisconnect);
	EVENT(OnPlayerLogin);
	EVENT(OnPlayerLogout);
	bool message(std::string channelName, std::string message, MessageType type);
};
bool InitChannels();