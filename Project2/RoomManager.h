#pragma once
#include <map>

class Room;
struct RoomID;

class RoomManager {

	std::map<const RoomID&, Room&> _rooms;

public:

	bool exists(const RoomID& room_to_find);
	bool add(const Room& room_to_add);
	const Room* get(const RoomID& id) const;

};