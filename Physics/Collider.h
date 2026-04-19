#pragma once

#include <SDL.h>

using Box = SDL_Rect;

class Collider
{
public:
	inline Box Get() { return ColliderBox; }
	inline void SetBuffer(int x, int y, int w, int h) { ColliderBuffer = { x, y, w, h }; }

	void Set(int x, int y, int w, int h)
	{
		ColliderBox =
		{
			x,
			y,
			w,
			h
		};
	}
private:

	Box ColliderBox;
	Box ColliderBuffer;
};

