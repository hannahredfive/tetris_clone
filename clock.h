#pragma once
#include <chrono>

class Clock
{
public:
	typedef std::chrono::high_resolution_clock ChronoClock;
	typedef unsigned long long u64;

	Clock();
	double TNow(); // in seconds

	static const double dT60Fps;

private:
	ChronoClock		_chronoclock;
	u64				_countNsStartUp;
};
