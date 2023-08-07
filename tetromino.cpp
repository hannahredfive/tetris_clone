#include "tetromino.h"
#include "SDL2/include/SDL.h"

Tetromino::Tetromino()
{
	tet_tiles[0][0] = red;
	tet_tiles[0][1] = red;
	tet_tiles[0][2] = red;
	tet_tiles[0][3] = red;
	tet_tiles[1][0] = red;
	tet_tiles[1][1] = red;
	tet_tiles[1][2] = red;
	tet_tiles[1][3] = red;
	tet_tiles[2][0] = red;
	tet_tiles[2][1] = red;
	tet_tiles[2][2] = red;
	tet_tiles[2][3] = red;
	tet_tiles[3][0] = red;
	tet_tiles[3][1] = red;
	tet_tiles[3][2] = red;
	tet_tiles[3][3] = red;
}

Tetromino::~Tetromino()
{

}

Position Tetromino::get_pos()
{
	return pos;
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
