#include "Zone.h"
#include "Room.h"

bool Zone::add_room(const Room& room) {
	
	return _rooms->add(room);
}

bool Zone::connect_zone(const Zone& neighbor, const RoomID& from, const RoomID& to) {
}

bool Zone::room_exists(const RoomID& room_id) {
	return _rooms->exists(room_id);
}

std::vector<Zone&> Zone::get_neighbor_zones() {
}

const ZoneID& Zone::id() const {
	return _zoneID;
}