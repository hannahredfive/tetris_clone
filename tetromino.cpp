#include "tetromino.h"
#include "SDL2/include/SDL.h"
#include "InputWomanager.h"
#include "board.h"
#include "common.h"

Tetromino::Tetromino()
{
	for (int y = 0; y < s_height; ++y)
	{
		for (int x = 0; x < s_width; ++x)
		{
			tet_tiles[y][x] = purple;
		}
	}

	pos._x = 3;
	pos._y = 0;
}

Tetromino::~Tetromino()
{

}

Position Tetromino::get_pos()
{
	return pos;
}

void Tetromino::set_pos(int x, int y)
{
	pos._x = x;
	pos._y = y;
}

colors Tetromino::get_color(int x, int y)
{
	return tet_tiles[y][x];
}

// NOTES: 
	// As time passes, the Tetromino should move down

	// If player pressed the down arrow, the tetromino should move down at double time

	// If the player presses the up arrow, the tetromino should rotate through orientation on each press
		// Rotation should update the tet_tiles
		// Tiles should be empty where the tetromino is not in space
			// NOTE: On above, how will I make empty tiles not override the colored tiles of other pieces already placed?

	// If the player presses the right arrow, the Tetromino should move right

	// If the player presses the left arrow, the Tetromino should move left
