#pragma once
#include <vector>
#include "ZoneManager.h"
#include "ZoneID.h"
#include "RoomManager.h"

struct RoomID;

class Zone {

	RoomManager* _rooms;
	const ZoneID _zoneID;
public:
	explicit Zone(ZoneID& id) : _zoneID(id) {}
	~Zone() {}
	bool add_room(const Room& id);
	bool connect_zone(const Zone& neighbor, const RoomID& from, const RoomID& to);
	bool room_exists(const RoomID& room_id);
	std::vector<Zone&> get_neighbor_zones();
	const ZoneID& id() const;
};