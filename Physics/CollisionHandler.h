#pragma once

#include <list>
#include <memory>
#include <SDL.h>
#include <tuple>
#include "..\Geometry\Geometry2d.h"

using namespace std;

using BoolPair = tuple<bool, bool>;
class Actor;
struct ActorCollisionResult {
	Actor* hitActor = nullptr;     // nullptr if no collision
	Vector2d values;               // from GetCollisionValues — which axes collided
	Vector2d centerDistances;
};

class CollisionHandler
{
public:
	Vector2d GetCollisionValues(SDL_Rect a, SDL_Rect b, Vector2d& centerDistances);

	bool CheckRectCollision(SDL_Rect a, SDL_Rect b);

	BoolPair CheckAppWallCollision(SDL_Rect object);

	// Iterates actors and returns the first collision found with its values.
	// Does not modify the caller's state — physics response is the caller's responsibility.
	ActorCollisionResult CheckCollisionWithActors(
		SDL_Rect collider,
		const list<unique_ptr<Actor>>& actors,
		Actor* self);
		
	static CollisionHandler& GetInstance()
	{
		static CollisionHandler CollisionHandlerInstance;
		return CollisionHandlerInstance;
	}

private:
	CollisionHandler();
	
	int mColCount, mRowCount, mTileSize;
};