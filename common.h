#pragma once
#include "SDL2/include/SDL.h"

enum colors
{
	empty, orange, blue, yellow, cyan, green, purple, red
};

struct Position
{
	int	_x; // top left of object
	int	_y;
};
