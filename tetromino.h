#pragma once
#include "SDL2/include/SDL.h"

class Tetromino
{
public:
	Tetromino(int window_width, int window_height);
	~Tetromino();
	void Draw(SDL_Renderer*);
	// max space a tetronimo can exist in, including rotation
	static const int s_height = 4;
	static const int s_width = 4;
private:
	enum colors
	{
		empty, orange, blue, yellow, cyan, green, purple, red
	};

	// Do I need shapes? Each shape has a unique color
	// Perhaps it might be better to have Orientation
	enum shapes
	{
		o_ricky, b_ricky, c_z, ri_z, hero, teewee, smashboy
	};

	// tiles carries the data for what color each tile of the board is
	colors tiles[s_height][s_width];

	// don't think I need these for this class?
	/*
	int tile_w;
	int tile_h;
	int board_xpos;
	int board_ypos;
	*/
};
