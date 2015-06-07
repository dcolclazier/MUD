#pragma once

#include <string>
#include <map>
#include "log.h"

class LogManager
{
	std::map<std::string, Log*> _logFiles;

	Log* _masterLog;

public:
	~LogManager();
	bool InitLogs();
	bool write(std::string logName, std::string message);
	bool CreateLog(std::string logName, std::string filename);
	bool CreateLog(std::string logName);
	bool LogExists(std::string logName);

	
};