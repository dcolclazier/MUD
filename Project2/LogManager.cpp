#include "LogManager.h"


bool LogManager::InitLogs() {

	if (!LogExists("system")) {
		if (!CreateLog("system")) return false;
	}
	if (!LogExists("network")) {
		if (!CreateLog("network")) return false;
	}
	if (!LogExists("security")) {
		if (!CreateLog("channels")) return false;
	}
	if (!LogExists("channels")) {
		if (!CreateLog("channels")) return false;
	}
	if (!LogExists("world")) {
		if (!CreateLog("world")) return false;
	}

	return true;
}

LogManager::~LogManager() {
	for (auto log : _logFiles) {
		delete log.second;
	}
}

bool LogManager::write(std::string logName, std::string message) {
	_masterLog->write(logName, message);
	if (!LogExists(logName)) return false;
	_logFiles[logName]->write(message);
	return true;
}

bool LogManager::CreateLog(std::string logName, std::string filename) {
	if (LogExists(logName)) return false;

	_logFiles[logName] = new Log(logName, filename);
	return true;
}

bool LogManager::CreateLog(std::string logName) {
	return CreateLog(logName, logName + ".log");
}

bool LogManager::LogExists(std::string logName) {
	return _logFiles.count(logName) > 0;
}
