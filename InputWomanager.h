#pragma once
#include "SDL2/include/SDL.h"

enum InputType
{
	UpArrow,
	DownArrow,
	LeftArrow,
	RightArrow,
	SpaceBar,
	EnterKey,

	InputTypeMax,
};

class InputWomanager // inputwoman
{
public:
	InputWomanager();
	~InputWomanager();

	bool IsButtonDown(InputType in) const;
	void HandleEvent(SDL_Event e);

private:
	bool isDown[InputTypeMax];
};
