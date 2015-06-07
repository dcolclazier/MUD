#include "eventmanager.h"
#include <vector>

class NormalSocket;
class ListenSocket;
class Player;

class PlayerManager
{
	std::vector<Player*> _activePlayers;

	std::map<NormalSocket*, Player*> _linkDeadPlayers;

public:
	Player* allocate_player(ListenSocket* socket);
	bool make_linkdead(NormalSocket* socket, Player* player);
};