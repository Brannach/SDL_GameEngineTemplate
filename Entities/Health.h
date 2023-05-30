#pragma once
#include "Actor.h"
class Health : public Actor
{
public:
	Health();
	Health(Properties* pr) : Actor(pr)
	{
		
	};

	void Update(float delta);
	void Draw();

protected:

};

