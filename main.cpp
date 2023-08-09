#include <stdio.h>

#define SDL_MAIN_HANDLED 1
#include <SDL.h>
#include "board.h"
#include "tetromino.h"
#include "common.h"



// Use this macro to disable optimizations for anything after it in a file. Sometimes easier than switching to the
//	debug project

#define PRAGMA_OPTIMIZE_OFF __pragma(optimize("gts", off))

// Macros for doing some simple error checking of SDL functions. Will print the SDL error string to the console, and 
//	then break into the debugger where the error occurred.

#define SDL_ASSERT(value) if (!(value)) { printf("Error! %s\n", SDL_GetError()); __debugbreak(); }
#define SDL_ERRCHECK(value) if ((value) == -1) { printf("Error! %s\n", SDL_GetError()); __debugbreak(); }


// function: check for collision
	// based on the tetronimo's pos is
		// check for collision in the following scenarios 
			// sides of board
			// bottom of board
			// with other filled in tiles of board

// function: place a tetromino on the board
// while tetromino is not placed, is when it's pos or rotation changes
void place_piece(Board* board, Tetromino tet)
{
	// get the tetromino's data
	Position tet_pos = tet.get_pos();
	for (int y = 0; y < tet.s_height; ++y)
	{
		for (int x = 0; x < tet.s_width; ++x)
		{
			// update board's tiles color data
			colors tet_color = tet.get_color(x, y);
			board->set_colors(tet_color, tet_pos, x, y);
		}
	}
}

// function: remove a tetromino from the board


// function: randomly pick a tetromino


int main(int cpChz, char** apChzArg)
{
	// cpChz = count of pointers to null terminated strings of chars
	// apChzArg = array of pointers to null terminated strings arguments
	// this may be usefull later if I want to launch my game to a specific place

	(void)cpChz;
	(void)apChzArg;

	// Initialize SDL

	SDL_ERRCHECK(SDL_Init(SDL_INIT_VIDEO));

	// Create a window with the title 'Hello World' in the center of the screen with dimensions as defined by width & height

	int w_width = 680;
	int w_height = 480;

	SDL_Window* pWindow = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w_width, w_height, 0);
	SDL_ASSERT(pWindow);

	// Create an accelerated renderer we can draw to

	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_ASSERT(pRenderer);

	Board board(w_width, w_height);
	

	

	bool fRunWindow = true;
	while (fRunWindow)
	{
		// Check for any events the OS might have sent us, such as requesting the app close

		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				fRunWindow = false;
		}

		// Statefully set the color of the next render operation to pink

		SDL_ERRCHECK(SDL_SetRenderDrawColor(pRenderer, 0xFF, 0x00, 0xFF, 0xFF));

		// Clear the entire screen to the last set render draw color

		SDL_ERRCHECK(SDL_RenderClear(pRenderer));

		// Draw board in the window
		board.Draw(pRenderer);

		// Make tetris piece
		Tetromino tet;

		// Place piece
		place_piece(&board, tet);

		// Present the current state of the renderer to the window to be displayed by the OS

		SDL_RenderPresent(pRenderer);
	}
}
