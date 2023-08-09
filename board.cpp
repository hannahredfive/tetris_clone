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

	tile_w = 20;
	tile_h = 20;
	board_xpos = 240;
	board_ypos = 40;

	// testing colors!
	/*
	tiles[0][0] = blue;
	tiles[5][8] = cyan;
	tiles[18][3] = orange;
	tiles[12][6] = purple;
	tiles[8][9] = green;
	tiles[14][2] = yellow;
	tiles[3][2] = red;
	*/
}

Board::~Board()
{

}

void Board::set_colors(colors color, Position pos, int offset_x, int offset_y)
{
	tiles[pos._y + offset_y][pos._x + offset_x] = color;
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
