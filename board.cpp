#include <stdio.h>
#include "board.h"
#include "SDL2/include/SDL.h"
#include "common.h"

Board::Board(int window_width, int window_height)
{
	// initial board as empty
	for (int y = 0; y < s_height; ++y)
	{
		for (int x = 0; x < s_width; ++x)
		{
			tiles[y][x] = empty;
		}
	}

	// determine size of tiles and starting upper left corner of board
	// for now, tiles & board starting pos will be a hard coded, 
	// but in future I want to have it be responsive to the size of the window made in main.cpp

	window_w = window_width;
	window_h = window_height;
	tile_w = 20;
	tile_h = 20;
	board_xpos = 240;
	board_ypos = 40;
}

Board::~Board()
{

}

colors Board::get_color(int x, int y)
{
	return tiles[y][x];
}

void Board::set_colors(colors color, Position pos, int offset_x, int offset_y)
{
	tiles[pos._y + offset_y][pos._x + offset_x] = color;
}

void Board::delete_row(int y)
{
	for (y; y > 0; --y)
	{
		for (int x = 0; x < s_width; ++x)
		{
			tiles[y][x] = tiles[y - 1][x];
		}
	}
}

void Board::check_rows()
{
	int row_count = 0;
	for (int y = 0; y < s_height; ++y)
	{
		for (int x = 0; x < s_width; ++x)
		{
			if (tiles[y][x] != empty)
			{
				row_count += 1;
			}
			if (row_count == 10)
			{
				delete_row(y);
			}
		}
		row_count = 0;
	}

}

bool Board::is_game_over()
{
	for (int x = 0; x < s_width; ++x)
	{
		if (tiles[0][x] != empty)
		{
			return true;
		}
	}
	return false;
}

void Board::clear_board()
{
	*this = Board(window_w, window_h);
}

void Board::Draw(SDL_Renderer *renderer)
{
	for (int y = 0; y < s_height; ++y)
	{
		for (int x = 0; x < s_width; ++x)
		{
			// determine correct draw color for individual 
			switch (tiles[y][x])
			{
			case empty:
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				break;
			
			case orange:
				SDL_SetRenderDrawColor(renderer, 255, 125, 0, 255);
				break;

			case blue:
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				break;

			case yellow:
				SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
				break;

			case cyan:
				SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
				break;

			case green:
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				break;

			case purple:
				SDL_SetRenderDrawColor(renderer, 160, 0, 255, 255);
				break;

			case red:
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				break;
			}

			SDL_Rect tile{x * tile_w + board_xpos, y * tile_h + board_ypos, tile_w, tile_h};
			SDL_RenderFillRect(renderer, &tile);
		}
	}
}
