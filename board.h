#pragma once
#include "SDL2/include/SDL.h"

class Board
{
public:
	Board(int window_width, int window_height);
	~Board();
	void Draw(SDL_Renderer *);
	// set color func
	static const int s_height = 20;
	static const int s_width = 10;
private:
	enum colors
	{
		empty, orange, blue, yellow, cyan, green, purple, red
	};
	
	// tiles carries the data for what color each tile of the board is
	colors tiles[s_height][s_width];

	int tile_w;
	int tile_h;
	int board_xpos;
	int board_ypos;
};
