#pragma once
#include "RoomID.h"


//should implement from IEnterable, ILeaveable, ILookable, ISearchable, etc
class Room {

	//name - where does this come from?
	//description - load from file? hard coded for now? provided by script?
	//unique id - guid? could have upwards of 50k rooms some day...
	//location  -- struct x,y,z -- 4d? haha just kidding... kinda...
	const RoomID _id;

public:

	explicit Room(const RoomID& id)
		: _id(id) {
	}
	const RoomID& ID() const { return _id; }
	void enter();
	void refresh();
	void on_tick();
	void exit();


};
