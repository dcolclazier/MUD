#pragma once


#include "tinyxml.h"
#include <string>

class Database {
	Database();


	static Database* _instance;
public:
	~Database();

	static Database* Instance()  { 
		if (_instance == nullptr){
			_instance = new Database();
		} 
		return _instance;
	}

	TiXmlDocument file;

	// Quick reference to the users section
	TiXmlElement* UserListElement;

	TiXmlElement* GrabUserByName(std::string& name);

	//void Save();
};
