#pragma once

#include "SDL.h"

#include "Actor.h"
#include "..\Core\Engine.h"

class Brick : public Actor
{
public:
	Brick() {};
	Brick(Properties* pr) : Actor(pr) { BrickColor = { 0,0,0,0 }; };
	Brick(Properties* pr, SDL_Color brickColor) : Actor(pr) 
	{
		BrickColor = brickColor;
	};

	void Update(float delta);
	void Draw();

protected:
	SDL_Color BrickColor;
};

