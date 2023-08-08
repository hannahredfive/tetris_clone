#pragma once
#include "SDL2/include/SDL.h"
#include "InputWomanager.h"

struct Position
{
	int	_x; // top left of object
	int	_y;
};

class Tetromino
{
public:
	Tetromino();
	~Tetromino();

	Position get_pos();
	// get colors func
	
	// max space a tetronimo can exist in, including rotation
	static const int s_height = 4;
	static const int s_width = 4;
private:
	enum colors
	{
		empty, orange, blue, yellow, cyan, green, purple, red
	};

	enum orientation
	{
		left, up, right, down
	};

	// tet_tiles carries the data for what color each tile of the tetromino
	colors tet_tiles[s_height][s_width];

	Position pos;
};
