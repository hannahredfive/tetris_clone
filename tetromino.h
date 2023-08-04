#pragma once
#include "SDL2/include/SDL.h"
#include "InputWomanager.h"

struct Transform
{
	int	_x; // top left of object
	int	_y;
};

class Tetromino
{
public:
	Tetromino();
	~Tetromino();
	void Update(float dT, const InputWomanager* pInputWoman, double t);
	void Draw(SDL_Renderer*);
	
	// max space a tetronimo can exist in, including rotation
	static const int s_height = 4;
	static const int s_width = 4;
private:
	enum colors
	{
		empty, orange, blue, yellow, cyan, green, purple, red
	};

	// Do I need shapes? Each shape has a unique color
	// Perhaps it might be better to have Orientation
	/*
	enum shapes
	{
		o_ricky, b_ricky, c_z, ri_z, hero, teewee, smashboy
	};
	*/

	enum orientation
	{
		left, right, up, down
	};

	// tet_tiles carries the data for what color each tile of the tetromino
	colors tet_tiles[s_height][s_width];

	Transform xfm;

	// NOTE: Collider? I will need a way to prevent it overlapping with other pieces

};
