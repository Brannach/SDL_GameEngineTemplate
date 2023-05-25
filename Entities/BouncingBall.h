#pragma once

#include "Actor.h"

class BouncingBall : public Actor
{
public:
	BouncingBall();
	BouncingBall(Properties* pr) : Actor(pr) {};

	void Update(float delta);
};

