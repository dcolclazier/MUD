#pragma once
#include <string>
#include <vector>

class Player;
class Command;

class Parser
{
public:
	static std::vector<std::string> split(std::string& userInput, char split = ' ', int* wordCount = nullptr);
	static std::string join(std::vector<std::basic_string<char>> parts);
	static bool is_special(std::string& command);
	static std::string capitalize(std::string& input);
	static std::string lowercase(std::string& input);
	static std::vector<std::string> handle_special(std::string& command);
};





