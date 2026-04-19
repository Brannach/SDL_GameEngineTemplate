#pragma once
#include "Actor.h"
class Paddle : public Actor
{
public:
	Paddle();
	Paddle(const Properties& pr) : Actor(pr)
	{
		Force.X = 0.0;
		Force.Y = 0.0;
	};

	void Update(float delta);

protected:
	Vector2d Force;
};

