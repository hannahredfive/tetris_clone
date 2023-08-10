#pragma once
#include "SDL2/include/SDL.h"
#include "common.h"

class Board
{
public:
	Board(int window_width, int window_height);
	~Board();
	colors get_color(int x, int y);
	void set_colors(colors color, Position pos, int offset_x, int offset_y);
	void delete_row(int y);
	void check_rows();
	void Draw(SDL_Renderer *);
	static const int s_height = 20;
	static const int s_width = 10;

private:
	// tiles carries the data for what color each tile of the board is
	colors tiles[s_height][s_width];

	int tile_w;
	int tile_h;
	int board_xpos;
	int board_ypos;
};
