#include "Clock.h"

const double Clock::dT60Fps = 1.0 / 60.0;

Clock::Clock()
	: _chronoclock()
	, _countNsStartUp(0)
{
	ChronoClock::time_point tp = _chronoclock.now();
	_countNsStartUp = tp.time_since_epoch().count();
}

double Clock::TNow()
{
	ChronoClock::time_point tp = _chronoclock.now();
	u64 countNs = tp.time_since_epoch().count();
	double dNs = double(countNs - _countNsStartUp);
	return dNs / double(1e+9);
}