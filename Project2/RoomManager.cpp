#include "RoomManager.h"
#include "Room.h"

bool RoomManager::exists(const RoomID& id) {
	auto room = _rooms.find(id);
	return (room == _rooms.end()) ? false : true;
}

bool RoomManager::add(const Room& new_room) {
	auto id = new_room.ID();
	auto room = _rooms.find(id);
	if (room != _rooms.end()) return false; 
		
	_rooms[id] = new_room;
	return true;
}

const Room* RoomManager::get(const RoomID& id) const{
	auto room_pair = _rooms.find(id);
	if (room_pair != _rooms.end()) return &(*room_pair).second;
	return nullptr;
}