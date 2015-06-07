#pragma once

#include "Defines.h"

class Utilities {
public:
	static FLAG bit_set(FLAG flag, int pos);
	static FLAG bit_clear(FLAG flag, int pos);
	static bool bit_is_set(FLAG flag, int pos);
};