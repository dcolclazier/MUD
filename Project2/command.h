#pragma	once
#include "i_secure.h"
#include "Defines.h"
#include "Status.h"
#include <string>
#include <vector>

struct Status;
class Player;
class Command : public ISecure {
protected:
	std::string _name;
	std::vector<std::string> _aliases;
	std::vector<Status> _validStatus;
	FLAG _access;
public:
	std::string& name();
	void set_name(std::string val);
	void add_alias(std::string alias);
	void add_aliases(std::vector<std::string> aliases);
	bool contains_alias(std::string& alias);
	void add_status(Status status);
	void add_status(std::vector<Status> status);
	bool has_status(Status status);
	void set_access_level(FLAG access) override;
	FLAG get_access_level() const override;
	virtual void Execute(Player* player, std::string& verb, std::vector<std::string>& args);
	virtual ~Command() = 0;

	
};
inline Command::~Command() {}
