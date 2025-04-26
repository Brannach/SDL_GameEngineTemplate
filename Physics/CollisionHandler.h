#pragma once

#include <SDL.h>
#include <tuple>
#include "..\Geometry\Geometry2d.h"

using namespace std;

using BoolPair = tuple<bool, bool>;

class CollisionHandler
{
public:
	Vector2d GetCollisionValues(SDL_Rect a, SDL_Rect b, Vector2d& centerDistances);

	bool CheckRectCollision(SDL_Rect a, SDL_Rect b);

	BoolPair CheckAppWallCollision(SDL_Rect object);

	static CollisionHandler* GetInstance()
	{
		if (CollisionHandlerInstance != nullptr) return CollisionHandlerInstance;
		else return CollisionHandlerInstance = new CollisionHandler();
	}

private:
	CollisionHandler();

	static CollisionHandler* CollisionHandlerInstance;
	int mColCount, mRowCount, mTileSize;
};