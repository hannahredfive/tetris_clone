#include "tetromino.h"
#include "SDL2/include/SDL.h"
#include "InputWomanager.h"
#include "board.h"
#include "common.h"
#include <cstdlib>
#include <time.h>

Tetromino::Tetromino()
{
	
	for (int y = 0; y < s_height; ++y)
	{
		for (int x = 0; x < s_width; ++x)
		{
			tet_tiles[y][x] = empty;
		}
	}

	srand (time(NULL));
	colors color = colors(rand() % 7 + 1);

	switch (color)
	{
	case orange: // orange ricky
		tet_tiles[0][2] = orange;
		tet_tiles[1][0] = orange;
		tet_tiles[1][1] = orange;
		tet_tiles[1][2] = orange;
		break;

	case blue:  // blue ricky
		tet_tiles[0][0] = blue;
		tet_tiles[1][0] = blue;
		tet_tiles[1][1] = blue;
		tet_tiles[1][2] = blue;
		break;

	case yellow: // smashboy
		tet_tiles[0][1] = yellow;
		tet_tiles[0][2] = yellow;
		tet_tiles[1][1] = yellow;
		tet_tiles[1][2] = yellow;
		break;

	case cyan: // teewee
		tet_tiles[0][1] = cyan;
		tet_tiles[1][0] = cyan;
		tet_tiles[1][1] = cyan;
		tet_tiles[1][2] = cyan;
		break;

	case green: // cleveland z
		tet_tiles[0][0] = green;
		tet_tiles[0][1] = green;
		tet_tiles[1][1] = green;
		tet_tiles[1][2] = green;
		break;

	case purple: // rhode island z
		tet_tiles[0][3] = purple;
		tet_tiles[0][2] = purple;
		tet_tiles[1][2] = purple;
		tet_tiles[1][1] = purple;
		break;

	case red: // hero
		tet_tiles[0][2] = red;
		tet_tiles[1][2] = red;
		tet_tiles[2][2] = red;
		tet_tiles[3][2] = red;
		break;
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
