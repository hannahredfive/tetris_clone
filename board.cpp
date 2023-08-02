#include "board.h"
#include "SDL2/include/SDL.h"

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
}

Board::~Board()
{

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
				SDL_SetRenderDrawColor(renderer, 185, 0, 255, 255);
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
