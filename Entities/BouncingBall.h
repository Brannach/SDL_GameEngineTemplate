#pragma once

#include "Actor.h"

class BouncingBall : public Actor
{
public:
	BouncingBall();
	BouncingBall(Properties* pr) : Actor(pr) 
	{
		Force.X = 2.0;
		Force.Y = -2.0;
	};

	void Update(float delta);

protected:
	Vector2d Force;
};

