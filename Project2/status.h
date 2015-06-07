#pragma once
#include <string>

enum Stat {
	any, sitting, standing, resting, sleeping, dead
};

struct Status {
private:
	Stat stat;
public:
	Status() { stat = standing; }
	Status(Stat st) :stat(st) {}

	std::string to_string() {
		switch (stat) {
		case any:
			return "any";
		case sitting:
			return "sitting";
		case standing:
			return "standing";
		case resting:
			return "resting";
		case sleeping:
			return "sleeping";
		case dead:
			return "dead";
		default: return "";
		}

	}

	bool operator == (const Status rhs) { return stat == rhs.stat; }
	bool operator == (const Stat rhs) { return stat == rhs; }
	bool operator != (const Stat rhs) { return stat != rhs; }
	bool operator != (const Status rhs) { return stat != rhs.stat; }
	//void operator = (const Stat rhs) {  stat = rhs; }
};

