#include "tetromino.h"
#include "SDL2/include/SDL.h"
#include "InputWomanager.h"
#include "board.h"
#include "common.h"
#include <cstdlib>
#include <time.h>

Tetromino::Tetromino() :
	tet_tiles(),
	pos()

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
		tet_tiles[1][2] = orange;
		tet_tiles[2][0] = orange;
		tet_tiles[2][1] = orange;
		tet_tiles[2][2] = orange;
		pos._x = 3;
		pos._y = -1;
		break;

	case blue:  // blue ricky
		tet_tiles[1][0] = blue;
		tet_tiles[2][0] = blue;
		tet_tiles[2][1] = blue;
		tet_tiles[2][2] = blue;
		pos._x = 3;
		pos._y = -1;
		break;

	case yellow: // smashboy
		tet_tiles[1][1] = yellow;
		tet_tiles[1][2] = yellow;
		tet_tiles[2][1] = yellow;
		tet_tiles[2][2] = yellow;
		pos._x = 3;
		pos._y = -1;
		break;

	case cyan: // teewee
		tet_tiles[1][1] = cyan;
		tet_tiles[2][0] = cyan;
		tet_tiles[2][1] = cyan;
		tet_tiles[2][2] = cyan;
		pos._x = 3;
		pos._y = -1;
		break;

	case green: // cleveland z
		tet_tiles[1][0] = green;
		tet_tiles[1][1] = green;
		tet_tiles[2][1] = green;
		tet_tiles[2][2] = green;
		pos._x = 3;
		pos._y = -1;
		break;

	case purple: // rhode island z
		tet_tiles[1][3] = purple;
		tet_tiles[1][2] = purple;
		tet_tiles[2][2] = purple;
		tet_tiles[2][1] = purple;
		pos._x = 3;
		pos._y = -1;
		break;

	case red: // hero
		tet_tiles[0][2] = red;
		tet_tiles[1][2] = red;
		tet_tiles[2][2] = red;
		tet_tiles[3][2] = red;
		pos._x = 3;
		pos._y = 0;
		break;
	}
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

void Tetromino::change_color()
{
	*this = Tetromino();
}

void Tetromino::rotate()
{
	colors tet_tiles_copy[s_height][s_width];

	for (int i = 0; i < s_height; ++i)
	{
		for (int j = 0; j < s_width; ++j)
		{
			tet_tiles_copy[i][j] = tet_tiles[s_height - j - 1][i];
		}
	}

	for (int y = 0; y < s_height; ++y)
	{
		for (int x = 0; x < s_width; ++x)
		{
			tet_tiles[y][x] = tet_tiles_copy[y][x];
		}
	}
}
