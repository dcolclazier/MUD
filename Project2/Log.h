#pragma once
#include <string>

class Log {
	std::string _fileName;
	std::string _logType;
	//int maxLineCount = 900;

public:
	Log(std::string logType, std::string fileName);
	void write(std::string message);
	void write(std::string logType, std::string message);
	std::string get_timeStamp();
};


