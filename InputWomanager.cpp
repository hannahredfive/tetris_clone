#include "InputWomanager.h"
#include "SDL2/include/SDL.h"

InputWomanager::InputWomanager()
	: isDown()
{
	
}

InputWomanager::~InputWomanager()
{

}

bool InputWomanager::IsButtonDown(InputType in) const
{
    return isDown[in];
}

void InputWomanager::HandleEvent(SDL_Event e)
{
    //User presses a key
    if (e.type == SDL_KEYDOWN)
    {
        //Select surfaces based on key press
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            isDown[UpArrow] = true;
            break;

        case SDLK_DOWN:
            isDown[DownArrow] = true;
            break;

        case SDLK_LEFT:
            isDown[LeftArrow] = true;
            break;

        case SDLK_RIGHT:
            isDown[RightArrow] = true;
            break;

        case SDLK_SPACE:
            isDown[SpaceBar] = true;
            break;
        }
    }

    //User unpresses a key
    if (e.type == SDL_KEYUP)
    {
        //Select surfaces based on key press
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            isDown[UpArrow] = false;
            break;

        case SDLK_DOWN:
            isDown[DownArrow] = false;
            break;

        case SDLK_LEFT:
            isDown[LeftArrow] = false;
            break;

        case SDLK_RIGHT:
            isDown[RightArrow] = false;
            break;

        case SDLK_SPACE:
            isDown[SpaceBar] = false;
            break;
        }
    }
}