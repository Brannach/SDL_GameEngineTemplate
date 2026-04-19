#pragma once
#include "Actor.h"
class Health : public Actor
{
public:
	Health();
	Health(const Properties& pr) : Actor(pr)
	{
		
	};

	void Update(float delta);
	void Draw();

protected:

};

