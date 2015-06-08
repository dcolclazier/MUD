#pragma once

struct RoomID {
	int x;
	int y;
	int z;

};


class Room {

	//name - where does this come from?
	//description - load from file? hard coded for now? provided by script?
	//unique id - guid? could have upwards of 50k rooms some day...
	//location  -- struct x,y,z -- 4d? haha just kidding... kinda...
	RoomID Location;

	


public:


	explicit Room(const RoomID& location)
		: Location(location) {
	}

	void enter();
	void refresh();
	void on_tick();
	void exit();


};
