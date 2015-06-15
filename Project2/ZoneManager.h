#pragma once
#include <map>
#include "Zone.h"

class ZoneManager {

	std::map<const ZoneID&, Zone&> _zones;

public:
	ZoneManager();
	bool exists(const ZoneID& id) const;
	bool add_zone(const Zone& zone);
	const Zone* get_zone(const ZoneID& id) const;
	bool InitZones();
};