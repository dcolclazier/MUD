#include "ZoneManager.h"

ZoneManager::ZoneManager() {
}

bool ZoneManager::exists(const ZoneID& id) const {
	auto zone = _zones.find(id);
	return zone == _zones.end() ? false : true;
}

bool ZoneManager::add_zone(const Zone& zone) {
	auto id = zone.id();
	if (exists(id)) return false;
	_zones[id] = zone;
	return true;
}

const Zone* ZoneManager::get_zone(const ZoneID& id) const {
	
	if (exists(id)) return &_zones.at(id);
	return nullptr;
	/*auto zone_pair = _zones.find(id);
	if (zone_pair != _zones.end()) return &(*zone_pair).second;
	return nullptr;*/
}

bool ZoneManager::InitZones() {

	//for now, put zone creation ccode here?
}