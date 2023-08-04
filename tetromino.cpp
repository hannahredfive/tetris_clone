#include "tetromino.h"
#include "SDL2/include/SDL.h"

Tetromino::Tetromino()
{

}

Tetromino::~Tetromino()
{

}

void Tetromino::Update(float dT, const InputWomanager* pInputWoman, double t)
{
	// As time passes, the Tetromino should move down

	// If player pressed the down arrow, the tetromino should move down at double time

	// If the player presses the up arrow, the tetromino should rotate through orientation on each press
		// Rotation should update the tet_tiles
		// Tiles should be empty where the tetromino is not in space
			// NOTE: On above, how will I make empty tiles not override the colored tiles of other pieces already placed?

	// If the player presses the right arrow, the Tetromino should move right

	// If the player presses the left arrow, the Tetromino should move left
}

void Tetromino::Draw(SDL_Renderer* renderer)
{

}
