#pragma once

#include "Actor.h"

class BouncingBall : public Actor
{
public:
	BouncingBall();
	BouncingBall(Properties* pr) : Actor(pr) 
	{
		Force.X = 1.0;
		Force.Y = -1.0;
	};

	void Update(float delta);

protected:
	Vector2d Force;
};

