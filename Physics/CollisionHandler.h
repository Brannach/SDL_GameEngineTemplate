#pragma once

#include <SDL.h>

class CollisionHandler
{
public:
	bool CheckCollision(SDL_Rect a, SDL_Rect b);

	static CollisionHandler* GetInstance()
	{
		if (sInstance != nullptr) return sInstance;
		else return sInstance = new CollisionHandler();
	}

private:
	CollisionHandler();

	static CollisionHandler* sInstance;
	int mColCount, mRowCount, mTileSize;
};