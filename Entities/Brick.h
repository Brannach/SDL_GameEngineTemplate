#pragma once

#include "SDL.h"

#include "Actor.h"
#include "..\Core\Engine.h"

class Brick : public Actor
{
public:
	Brick() {};
	Brick(const Properties& pr) : Actor(pr) { BrickColor = { 0,0,0,0 }; };
	Brick(const Properties& pr, SDL_Color brickColor) : Actor(pr) 
	{
		BrickColor = brickColor;
	};
	bool ShouldDestroyOnCollision() const override { return true; }
	void Update(float delta);
	void Draw();

protected:
	SDL_Color BrickColor;
};

