#pragma once

#include "Actor.h"

class BouncingBall : public Actor
{
public:
	BouncingBall();
	BouncingBall(Properties* pr) : Actor(pr) 
	{
		ResetForce();
	};

	void Update(float delta);
	void ResetForce() {
		Force.X = 5.0;
		Force.Y = -5.0;
	}
protected:
	Vector2d Force;
};

