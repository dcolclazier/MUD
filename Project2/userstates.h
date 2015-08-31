#pragma	once
#include "World.h"

class IUserState;
class TiXmlElement;
class Player;
class World;

class PlayerNotFound : public IUserState
{
	Player* _player;
	std::string _chosenName;
public:

	PlayerNotFound(Player* player, std::string name) : _player(player), _chosenName(name)	{}

	void deactivate() override;
	void activate() override;
	void run() override;
};


class Authenticated : public IUserState {
	Player* _player;
	TiXmlElement* _userData;

public:
	Authenticated(Player* player) : _player(player) {}
	void deactivate() override;
	void activate() override;
	void run() override;
};

class Connected : public IUserState {

	Player* _player;
	World* _world;

public:
	explicit Connected(Player* player) : _player(player), _world(World::world()) {}
	void deactivate() override;
	void activate() override;
	void run() override;

};

class CreateUserState : public IUserState {
	Player* _player;
	TiXmlElement* _userData;
	bool _confirming;
	std::string _userName;
	World* _world;
public:
	CreateUserState(Player* player, std::string userName);
	void deactivate() override;
	void activate() override;
	void run() override;

};

class LoginState :public IUserState {
	Player* _player;
	int _failedAttempts;

public:
	explicit LoginState(Player* player, int failedCount) : _player(player), _failedAttempts(failedCount) {}
	void deactivate() override;
	void activate() override;
	void run() override;

};