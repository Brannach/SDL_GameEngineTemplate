#pragma once

#include "Actor.h"

class BouncingBall : public Actor
{
public:
	BouncingBall();
	BouncingBall(const Properties& pr) : Actor(pr) 
	{
		ResetForce();
	};

	void Update(float delta);
	void ResetForce() {
		Force.X = 1.0;
		Force.Y = -1.0;
	}
protected:
	Vector2d Force;
};

