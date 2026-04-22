#include "CollisionHandler.h"
#include "..\Core\Engine.h"
#include "..\Core\MainApplication.h"
#include "..\Entities\Actor.h"

using namespace std;
CollisionHandler::CollisionHandler()
{
}
Vector2d CollisionHandler::GetCollisionValues(SDL_Rect a, SDL_Rect b, Vector2d& centerDistances )
{
    float aHalfW = (float)a.w / 2;
    float aHalfH = (float)a.h / 2;
    float bHalfW = (float)b.w / 2;
    float bHalfH = (float)b.h / 2;
    float aCenterX = (float)a.x + a.w / 2;
    float aCenterY = (float)a.y + a.h / 2;
    float bCenterX = (float)b.x + b.w / 2;
    float bCenterY = (float)b.y + b.h / 2;

    // Calculate the distance between centers
    float diffX = aCenterX - bCenterX;
    float diffY = aCenterY - bCenterY;

    //Needed to know on which side (along the X axis) of the paddle center the ball collided
    centerDistances.X = diffX;
    centerDistances.Y = diffY;

    // Calculate the minimum distance to separate along X and Y
    float minXDist = aHalfW + bHalfW;
    float minYDist = aHalfH + bHalfH;

    // Calculate the depth of collision for both the X and Y axis
    float depthX = diffX > 0 ? minXDist - diffX : -minXDist - diffX;
    float depthY = diffY > 0 ? minYDist - diffY : -minYDist - diffY;
    
    // Now that you have the depth, you can pick the smaller depth and move
    // along that axis.
    if (depthX != 0 && depthY != 0) {
        if (abs(depthX) < abs(depthY)) {
            // Collision along the Y axis
            return Vector2d(-1.0, 1.0);
        }
        else {
            // Collision along the X axis.
            return Vector2d(1.0 * abs(diffX), -1.0);
        }
    }
    return Vector2d (1.0, 1.0);
}

bool CollisionHandler::CheckRectCollision(SDL_Rect a, SDL_Rect b)
{
    bool xOverlap = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool yOverlap = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return xOverlap && yOverlap;
}

BoolPair CollisionHandler::CheckAppWallCollision(SDL_Rect object)
{

    bool xOverlap = (object.x < 0) || (object.x + object.w > DEFAULT_SCREEN_WIDTH);
    bool yOverlap = (object.y < 0) || (object.y + object.h > Engine::GetInstance().GetGameplayRules()->GetHealthLossLimit());
    return make_tuple(xOverlap, yOverlap);
}

ActorCollisionResult CollisionHandler::CheckCollisionWithActors(
    SDL_Rect collider,
    const std::list<std::unique_ptr<Actor>>& actors,
    Actor* self)
{
    for (const auto& actor : actors)
    {
        if (!actor->CanCollide() || actor.get() == self)
            continue;

        if (!CheckRectCollision(collider, actor->GetCollider().Get()))
            continue;

        ActorCollisionResult result;
        result.hitActor = actor.get();
        result.values = GetCollisionValues(collider, actor->GetCollider().Get(), result.centerDistances);
        return result;
    }
    return {};
}