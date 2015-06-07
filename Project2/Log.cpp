#include "Log.h"
#include <time.h>
#include <sstream>
#include <fstream>
#include <iostream>


Log::Log(std::string logType, std::string fileName) : _fileName(fileName), _logType(logType) {}

void Log::write(std::string message)
{
	std::fstream fout;
	fout.open(_fileName, std::fstream::out | std::fstream::app);
	fout << get_timeStamp() << " - "
		<< "[" << _logType << "]" << " "
		<< message << std::endl;
	fout.close();
}
void Log::write(std::string logType, std::string message)
{
	std::fstream fout;
	fout.open("masterlog.log", std::fstream::out | std::fstream::app);
	fout << get_timeStamp() << " - "
		<< "[" << logType << "]" << " "
		<< message << std::endl;
	fout.close();
}
std::string Log::get_timeStamp() {
	std::ostringstream oss;
	struct tm currentTime;
	__time64_t rawTime;

	_time64(&rawTime);
	_localtime64_s(&currentTime, &rawTime);

	oss << currentTime.tm_mon + 1 << "/"
		<< currentTime.tm_mday << "/"
		<< currentTime.tm_year + 1900 << " "
		<< currentTime.tm_hour << ":"
		<< currentTime.tm_min << ":"
		<< currentTime.tm_sec;

	return oss.str();

}