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

	t_lastHmove = 0;
	t_lastVmove = 0;

}

Tetromino::~Tetromino()
{

}

Position Tetromino::get_pos()
{
	return pos;
}

void Tetromino::update(double t, const InputWomanager* pInputWoman)
{
	double h_diff = t - t_lastHmove;
	double v_diff = t - t_lastVmove;
	if (h_diff < 0.5)
	{
		return;
	}

	// left or right movement
	// need to add delta time to see incremental movement

	if (pInputWoman->IsButtonDown(InputType::LeftArrow))
	{
		if (pos._x > 0)
		{
			pos._x -= 1;
			t_lastHmove = t;
		}
	}

	else if (pInputWoman->IsButtonDown(InputType::RightArrow))
	{
		// this boundary is because of the 4x4 tet tile size
		// I will need account for empty cells moving forward
		// but this will do for now!
		if (pos._x < Board::s_width - s_width)
		{
			pos._x += 1;
			t_lastHmove = t;
		}
	}

	if (v_diff < 1)
	{
		return;
	}

	if (pos._y < Board::s_height - s_height)
	{
		pos._y += 1;
		t_lastVmove = t;
	}
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
