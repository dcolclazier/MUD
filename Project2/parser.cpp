#include "parser.h"
#include <sstream>
#include <algorithm>

std::vector<std::string> Parser::split(std::string& userInput, char split, int* wordCount) {
	std::string s;
	std::istringstream iss(userInput);
	std::vector<std::string> words;
	while (getline(iss, s, split)) {
		words.push_back(s);
	}
	if (wordCount) *wordCount = words.size();
	return words;
}

std::string Parser::join(std::vector<std::string> parts) {
	std::stringstream ss;
	for (auto part : parts) {
		if (part == parts.front()) {
			ss << part;
			continue;
		}
		ss << " " << part;
	}
	return ss.str();
}

bool Parser::is_special(std::string& command)
{
	switch (command[0])
	{
	case '\'':
	case '\"':
	case ':':
		return true;
	default:
		return false;
	}
}

std::string Parser::lowercase(std::string& input)
{
	auto ret = input;
	transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
	return ret;
}

std::string Parser::capitalize(std::string& input)
{
	auto ret = input;
	transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
	return ret;
}

std::vector<std::string> Parser::handle_special(std::string& command)
{
	switch (command[0])  {
	case '\'': 
	case '\"': 
		command.replace(0, 1, "say ");
		break;
	case ':':
		command.replace(0, 1, "emote ");
	}
	return split(command);
}
