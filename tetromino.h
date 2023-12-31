#pragma once
#include "SDL2/include/SDL.h"
#include "InputWomanager.h"
#include "common.h"



class Tetromino
{
public:
	Tetromino();
	~Tetromino();

	Position get_pos();
	void set_pos(int x, int y);
	colors get_color(int x, int y);
	void change_color();
	void rotate();
	
	// max space a tetronimo can exist in, including rotation
	static const int s_height = 4;
	static const int s_width = 4;

private:
	// tet_tiles carries the color data for each tile of the tetromino
	colors tet_tiles[s_height][s_width];
	Position pos;
};
