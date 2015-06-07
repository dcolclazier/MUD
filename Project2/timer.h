#pragma once

#include <chrono>

class Timer {
	typedef std::chrono::high_resolution_clock _clock;
	typedef std::chrono::duration<long double, std::ratio<1> > _second;
	std::chrono::time_point<_clock> _begin;
public:
	Timer() : _begin(_clock::now()) {}
	void reset() { _begin = _clock::now(); }
	long double elapsed() const {
		return std::chrono::duration_cast<_second>(_clock::now() - _begin).count();
	}
};