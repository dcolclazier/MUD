#include "utilities.h"

FLAG Utilities::bit_set(FLAG flag, int pos) {
	return flag |= pos;
}
FLAG Utilities::bit_clear(FLAG flag, int pos) {
	return flag &= ~pos;
}
bool Utilities::bit_is_set(FLAG flagToCheck, int whichBit) {
	//return (flag & pos) == pos;
	return (flagToCheck & whichBit) == flagToCheck;
}