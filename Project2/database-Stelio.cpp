#include "Database.h"
Database* Database::_instance = nullptr;

Database::Database() {
	file.LoadFile("mud.xml");
	// note this file must already have the parent element, "muddata"

	// grab the player list or make one - makes it easy later
	UserListElement = file.FirstChildElement("muddata")->FirstChildElement("playerlist");
	if (UserListElement == nullptr) {
		// Note that LinkEndChild gives the element to TinyXML, which will handle and delete it as necessary
		UserListElement = new TiXmlElement("playerlist");
		file.LinkEndChild(UserListElement);
	}
}

Database::~Database() {
	file.SaveFile("mud.xml");
//	delete _instance;
}

TiXmlElement* Database::GrabUserByName(std::string& name) {
	// Grab the first player node
	// retval will be returned as and if we find the player with the correct name
	TiXmlNode* retval = UserListElement->FirstChildElement("player");

	while (retval != nullptr) {
		// is it an element?
		// does it have the same name as we want?
		int null = 0;
		if (retval->ToElement() && static_cast<TiXmlElement*>(retval)->Attribute("name") == name) {
			return static_cast<TiXmlElement*>(retval);
		}
		// Grab the next return value
		retval = UserListElement->IterateChildren("player", retval);
	}
	return nullptr;
}


