#pragma once

#include <map>
#include "channel.h"
#include "eventmanager.h"

class ChannelManager  {

	std::map<std::string, Channel*> _channelList;

public:
	bool InitChannels();
	bool join_channel(const std::string& channelName, Player* playerToJoin);
	bool leave_channel(const std::string& channelName, Player* playerToJoin);
	bool add_channel(const std::string& channelName, FLAG channelAccessLevel);
	bool remove_channel(const std::string& channelName);
	bool channel_exists(const std::string& channelName);
	
	EVENT(OnDirtyDisconnect);
	EVENT(OnPlayerLogin);
	EVENT(OnPlayerLogout);
	bool message(const std::string& channelName, const std::string& message, MessageType type);
};
bool InitChannels();