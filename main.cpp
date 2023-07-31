#include <stdio.h>

#define SDL_MAIN_HANDLED 1
#include <SDL.h>



// Use this macro to disable optimizations for anything after it in a file. Sometimes easier than switching to the
//	debug project

#define PRAGMA_OPTIMIZE_OFF __pragma(optimize("gts", off))

// Macros for doing some simple error checking of SDL functions. Will print the SDL error string to the console, and 
//	then break into the debugger where the error occurred.

#define SDL_ASSERT(value) if (!(value)) { printf("Error! %s\n", SDL_GetError()); __debugbreak(); }
#define SDL_ERRCHECK(value) if ((value) == -1) { printf("Error! %s\n", SDL_GetError()); __debugbreak(); }



int main(int cpChz, char** apChzArg)
{
	// cpChz = count of pointers to null terminated strings of chars
	// apChzArg = array of pointers to null terminated strings arguments
	// this may be usefull later if I want to launch my game to a specific place

	(void)cpChz;
	(void)apChzArg;

	// Initialize SDL

	SDL_ERRCHECK(SDL_Init(SDL_INIT_VIDEO));

	// Create a window with the title 'Hello World' in the center of the screen with dimensions 640x480

	SDL_Window* pWindow = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	SDL_ASSERT(pWindow);

	// Create an accelerated renderer we can draw to

	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_ASSERT(pRenderer);

	// Statefully set the color of the next render operation to pink

	SDL_ERRCHECK(SDL_SetRenderDrawColor(pRenderer, 0xFF, 0x00, 0xFF, 0xFF));

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

		// Clear the entire screen to the last set render draw color

		SDL_ERRCHECK(SDL_RenderClear(pRenderer));

		// Present the current state of the renderer to the window to be displayed by the OS

		SDL_RenderPresent(pRenderer);
	}
}
