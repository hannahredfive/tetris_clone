#include <stdio.h>

#define SDL_MAIN_HANDLED 1
#include <SDL.h>
#include <SDL_ttf.h>
#include "board.h"
#include "tetromino.h"
#include "common.h"
#include "clock.h"
#include "InputWomanager.h"



// Use this macro to disable optimizations for anything after it in a file. Sometimes easier than switching to the
//	debug project

#define PRAGMA_OPTIMIZE_OFF __pragma(optimize("gts", off))

// Macros for doing some simple error checking of SDL functions. Will print the SDL error string to the console, and 
//	then break into the debugger where the error occurred.

#define SDL_ASSERT(value) if (!(value)) { printf("Error! %s\n", SDL_GetError()); __debugbreak(); }
#define SDL_ERRCHECK(value) if ((value) == -1) { printf("Error! %s\n", SDL_GetError()); __debugbreak(); }

enum GameState
{
	StartMenu,
	GamePlay,
	GameOver,
};


bool collision(Board * pboard, Tetromino * ptet)
{
	Position pos = ptet->get_pos();

	for (int y = 0; y < ptet->s_height; ++y)
	{
		for (int x = 0; x < ptet->s_width; ++x)
		{
			if (ptet->get_color(x, y) != empty)
			{
				int board_x = pos._x + x;
				int board_y = pos._y + y;
	
				// sides of board
				if (board_x < 0 || board_x > 9)
				{
					return false;
				}
	
				// bottom of board
				if (board_y > 19)
				{
					return false;
				}

				// with other filled in tiles of board
				if (pboard->get_color(board_x, board_y) != empty)
				{
					return false;
				}
			}
		}
	}
	return true;
}


void place_piece(Board* pboard, Tetromino* ptet)
{
	// get the tetromino's data
	Position tet_pos = ptet->get_pos();
	for (int y = 0; y < ptet->s_height; ++y)
	{
		for (int x = 0; x < ptet->s_width; ++x)
		{
			// update board's tiles color data
			colors tet_color = ptet->get_color(x, y);
			if (tet_color != empty)
			{
				pboard->set_colors(tet_color, tet_pos, x, y);
			}
		}
	}
}


void pickup_piece(Board* pboard, Tetromino* ptet)
{
	// get the tetromino's data
	Position tet_pos = ptet->get_pos();
	for (int y = 0; y < ptet->s_height; ++y)
	{
		for (int x = 0; x < ptet->s_width; ++x)
		{
			if (ptet->get_color(x, y) != empty)
			{
				// update board's tiles color data to empty
				colors color = empty;
				pboard->set_colors(color, tet_pos, x, y);
			}
		}
	}
}


void update_piece(GameState* pgamestate, InputWomanager* pInputWoman, Board* pboard, Tetromino* ptet, double t, double* pt_lastXmove, double* pt_lastYmove, double* pt_lastRmove)
{
	// pickup piece
	pickup_piece(pboard, ptet);

	// Get tet data
	Position pos = ptet->get_pos();

	// find time since last movement on x & y
	double x_diff = t - *pt_lastXmove;
	double y_diff = t - *pt_lastYmove;
	double r_diff = t - *pt_lastRmove;

	if (r_diff > 0.25)
	{
		// rotate
		if (pInputWoman->IsButtonDown(InputType::UpArrow))
		{
			ptet->rotate();
			if (!collision(pboard, ptet))
			{
				ptet->rotate();
				ptet->rotate();
				ptet->rotate();
			}
			*pt_lastRmove = t;
		}
	}

	if (x_diff > 0.5)
	{
		// left movement
		if (pInputWoman->IsButtonDown(InputType::LeftArrow))
		{
			pos._x -= 1;
			ptet->set_pos(pos._x, pos._y);
			if (!collision(pboard, ptet))
			{
				pos._x += 1;
				ptet->set_pos(pos._x, pos._y);
			}
			*pt_lastXmove = t;
		}

		// right movement
		if (pInputWoman->IsButtonDown(InputType::RightArrow))
		{
			pos._x += 1;
			ptet->set_pos(pos._x, pos._y);
			if (!collision(pboard, ptet))
			{
				pos._x -= 1;
				ptet->set_pos(pos._x, pos._y);
			}
			*pt_lastXmove = t;
		}
	}

	// downpress makes the piece fall faster
	if (y_diff > 0.15 && pInputWoman->IsButtonDown(InputType::DownArrow))
	{
		pos._y += 1;
		ptet->set_pos(pos._x, pos._y);
		if (!collision(pboard, ptet))
		{
			pos._y -= 1;
			ptet->set_pos(pos._x, pos._y);
			place_piece(pboard, ptet);
			pboard->check_rows();
			ptet->change_color();

			// Check for Game Over
			if (pboard->is_game_over())
			{
				*pgamestate = GameOver;
				return;
			}
		}
		*pt_lastYmove = t;
		place_piece(pboard, ptet);
	}
	else if (y_diff < 1)
	{
		place_piece(pboard, ptet);
	}
	// normal falling!
	else
	{
		pos._y += 1;
		ptet->set_pos(pos._x, pos._y);
		if (!collision(pboard, ptet))
		{
			pos._y -= 1;
			ptet->set_pos(pos._x, pos._y);
			place_piece(pboard, ptet);
			pboard->check_rows();
			ptet->change_color();

			// Check for Game Over
			if (pboard->is_game_over())
			{
				*pgamestate = GameOver;
				return;
			}
		}
		*pt_lastYmove = t;
		place_piece(pboard, ptet);
	}
}

void start_menu(GameState* pgamestate, SDL_Renderer* pRenderer, TTF_Font* title_font, SDL_Color title_color, TTF_Font* instr_font, SDL_Color instr_color, InputWomanager* pInputWoman, int w_width, int w_height)
{
	// Start Game Title
	SDL_Surface* surf_start_title = TTF_RenderText_Solid(title_font, "Hannah's Tetris Clone", title_color);
	SDL_Texture* start_title = SDL_CreateTextureFromSurface(pRenderer, surf_start_title);
	SDL_Rect start_title_rect;
	start_title_rect.x = w_width / 2 - surf_start_title->w / 2;
	start_title_rect.y = w_height / 2 - surf_start_title->h;
	start_title_rect.w = surf_start_title->w;
	start_title_rect.h = surf_start_title->h;

	// Start Game Instructions
	SDL_Surface* surf_start_inst = TTF_RenderText_Solid(instr_font, "Press spacebar to begin playing!", instr_color);
	SDL_Texture* start_inst = SDL_CreateTextureFromSurface(pRenderer, surf_start_inst);
	SDL_Rect start_inst_rect;
	start_inst_rect.x = w_width / 2 - surf_start_inst->w / 2;
	start_inst_rect.y = w_height / 2;
	start_inst_rect.w = surf_start_inst->w;
	start_inst_rect.h = surf_start_inst->h;

	// Render Title & Instructions
	SDL_RenderCopy(pRenderer, start_title, NULL, &start_title_rect);
	SDL_RenderCopy(pRenderer, start_inst, NULL, &start_inst_rect);

	// Check for Spacebar Use
	if (pInputWoman->IsButtonDown(InputType::SpaceBar))
	{
		*pgamestate = GamePlay;
	}

	// Clean up
	SDL_DestroyTexture(start_title);
	SDL_FreeSurface(surf_start_title);
	SDL_DestroyTexture(start_inst);
	SDL_FreeSurface(surf_start_inst);
}

void play_game(GameState* pgamestate, Board* pboard, Tetromino* ptet, SDL_Renderer* pRenderer, InputWomanager* pInputWoman, float& t_since_start, double dT, double* pt_lastXmove, double* pt_lastYmove, double* pt_lastRmove, TTF_Font* controls_font, TTF_Font* time_font, SDL_Color time_color, TTF_Font* title_font, SDL_Color title_color, TTF_Font* game_over_font, SDL_Color game_over_color, int w_width, int w_height)
{
	// Gameplay Title
	SDL_Surface* surface_title_message = TTF_RenderText_Solid(title_font, "Hannah's Tetris Clone", title_color);
	SDL_Texture* title_message = SDL_CreateTextureFromSurface(pRenderer, surface_title_message);
	SDL_Rect title_message_rect;
	title_message_rect.x = w_width / 2 - surface_title_message->w / 2;
	title_message_rect.y = 5;
	title_message_rect.w = surface_title_message->w;
	title_message_rect.h = surface_title_message->h;
	SDL_RenderCopy(pRenderer, title_message, NULL, &title_message_rect);

	// Set up Time Tracker text
	int mins_playing = int(t_since_start) / 60;
	int secs_playing = t_since_start - mins_playing * 60;
	char chars[32];
	sprintf_s(chars, "%02d:%02d", mins_playing, secs_playing);
	SDL_Surface* surface_time_message = TTF_RenderText_Solid(time_font, chars, time_color);
	SDL_Texture* time_message = SDL_CreateTextureFromSurface(pRenderer, surface_time_message);
	SDL_Rect time_message_rect;
	// 200 = board total width
	time_message_rect.x = 120 - surface_time_message->w / 2;
	time_message_rect.y = w_height / 2 - surface_time_message->h / 2;
	time_message_rect.w = surface_time_message->w;
	time_message_rect.h = surface_time_message->h;
	SDL_RenderCopy(pRenderer, time_message, NULL, &time_message_rect);

	// Set up Controller Instructions text
	SDL_Surface* surface_controls = TTF_RenderText_Blended_Wrapped(controls_font, "^ = Rotate\n< = Move Left\n> = Move Right\nv = Fall Fast", time_color, 0);
	SDL_Texture* controls = SDL_CreateTextureFromSurface(pRenderer, surface_controls);
	SDL_Rect controls_rect;
	// 200 = board total width
	controls_rect.x = 560 - surface_controls->w / 2;
	controls_rect.y = w_height / 2 - surface_controls->h / 2;
	controls_rect.w = surface_controls->w;
	controls_rect.h = surface_controls->h;
	SDL_RenderCopy(pRenderer, controls, NULL, &controls_rect);

	// Draw board in the window
	pboard->Draw(pRenderer);

	// Update piece data if in GamePlay state
	if (*pgamestate == GamePlay)
	{
		t_since_start += 1.0 / 60.0;
		update_piece(pgamestate, pInputWoman, pboard, ptet, t_since_start, pt_lastXmove, pt_lastYmove, pt_lastRmove);
	}
	else
	{
		// Game Over Text
		SDL_Surface* surface_game_over = TTF_RenderText_Blended_Wrapped(game_over_font, "GAME\nOVER", game_over_color, 0);
		SDL_Texture* game_over = SDL_CreateTextureFromSurface(pRenderer, surface_game_over);
		SDL_Rect game_over_rect;
		game_over_rect.x = w_width / 2 - surface_game_over->w / 2;
		game_over_rect.y = w_height / 2 - surface_game_over->h / 2;
		game_over_rect.w = surface_game_over->w;
		game_over_rect.h = surface_game_over->h;
		SDL_RenderCopy(pRenderer, game_over, NULL, &game_over_rect);

		// Return to Start Menu Instructions Text
		SDL_Surface* surface_return_message = TTF_RenderText_Blended(controls_font, "Press ENTER to return to the start menu!", time_color);
		SDL_Texture* return_message = SDL_CreateTextureFromSurface(pRenderer, surface_return_message);
		SDL_Rect return_message_rect;
		return_message_rect.x = w_width / 2 - surface_return_message->w / 2;
		return_message_rect.y = (w_height / 4) * 3 - surface_return_message->h / 2;
		return_message_rect.w = surface_return_message->w;
		return_message_rect.h = surface_return_message->h;
		SDL_RenderCopy(pRenderer, return_message, NULL, &return_message_rect);

		// Check for EnterKey Use
		if (pInputWoman->IsButtonDown(InputType::EnterKey))
		{
			*pgamestate = StartMenu;
			pboard->clear_board();
			t_since_start = 0;
			*pt_lastXmove = 0; 
			*pt_lastYmove = 0; 
			*pt_lastRmove = 0;
		}

		// Clean Up Text Rendering
		SDL_DestroyTexture(game_over);
		SDL_FreeSurface(surface_game_over);
		SDL_DestroyTexture(return_message);
		SDL_FreeSurface(surface_return_message);
	}
	
	// Clean Up Text Rendering
	SDL_DestroyTexture(title_message);
	SDL_FreeSurface(surface_title_message);
	SDL_DestroyTexture(time_message);
	SDL_FreeSurface(surface_time_message);
	SDL_DestroyTexture(controls);
	SDL_FreeSurface(surface_controls);
}


int main(int cpChz, char** apChzArg)
{
	// cpChz = count of pointers to null terminated strings of chars
	// apChzArg = array of pointers to null terminated strings arguments
	// this may be usefull later if I want to launch my game to a specific place

	(void)cpChz;
	(void)apChzArg;

	// Initialize SDL
	SDL_ERRCHECK(SDL_Init(SDL_INIT_VIDEO));
	SDL_ERRCHECK(TTF_Init());

	// Create a window with dimensions as defined by width & height
	int w_width = 680;
	int w_height = 480;

	SDL_Window* pWindow = SDL_CreateWindow("Hannah's Tetris Clone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w_width, w_height, 0);
	SDL_ASSERT(pWindow);

	// Create an accelerated renderer we can draw to
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_ASSERT(pRenderer);

	// Font & Color Set Up
	TTF_Font* silkbold = TTF_OpenFont("fonts\\Silkscreen-Bold.ttf", w_width / 30);
	TTF_Font* silkboldBIG = TTF_OpenFont("fonts\\Silkscreen-Bold.ttf", w_width / 20);
	TTF_Font* silkboldHUGE = TTF_OpenFont("fonts\\Silkscreen-Bold.ttf", w_width / 10);
	TTF_Font* silk = TTF_OpenFont("fonts\\Silkscreen-Regular.ttf", w_width / 17);
	TTF_Font* silksmall = TTF_OpenFont("fonts\\Silkscreen-Regular.ttf", w_width / 28);
	TTF_Font* silksmaller = TTF_OpenFont("fonts\\Silkscreen-Regular.ttf", w_width / 34);
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Color purple = { 115, 93, 130, 255 };
	// SDL_Color purple = { 119, 88, 178, 255 };

	// Movement tracking
	// game time
	double t_lastXmove = 0;
	double t_lastYmove = 0;
	double t_lastRmove = 0;

	// Time in game tracking
	// game time
	float t_since_start = 0.0;

	// Set up needed game elements
	GameState gamestate = StartMenu;
	InputWomanager inputwoman;
	Board board(w_width, w_height);
	Tetromino tet;
	Clock clock;
	double t = clock.TNow();
	double dT = Clock::dT60Fps;

	// Launch window game loop
	bool fRunWindow = true;
	while (fRunWindow)
	{
		// Check for any events the OS might have sent us, such as requesting the app close
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				fRunWindow = false;
			else
				inputwoman.HandleEvent(event);
		}

		// Statefully set the color of the next render operation to a pale sage green
		SDL_ERRCHECK(SDL_SetRenderDrawColor(pRenderer, 132, 169, 140, 255));

		// Clear the entire screen to the last set render draw color
		SDL_ERRCHECK(SDL_RenderClear(pRenderer));

		// Based on GameState switch between game modes
		switch (gamestate)
		{
		case StartMenu:
			start_menu(&gamestate, pRenderer, silkboldBIG, purple, silksmall, white, &inputwoman, w_width, w_height);
			break;

		case GameOver:
		case GamePlay:
			play_game(&gamestate, &board, &tet, pRenderer, &inputwoman, t_since_start, dT, &t_lastXmove, &t_lastYmove, &t_lastRmove, silksmaller, silk, white, silkbold, purple, silkboldHUGE, white, w_width, w_height);
			break;
		}

		// Present the current state of the renderer to the window to be displayed by the OS
		SDL_RenderPresent(pRenderer);

		// Maintain DT
		double tNew;
		do
		{
			tNew = clock.TNow();
			dT = tNew - t;
			SDL_Delay(0);
		} while (dT < Clock::dT60Fps);
		t = tNew;
	}
}
