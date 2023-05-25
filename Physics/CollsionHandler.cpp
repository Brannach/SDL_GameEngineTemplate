#include "CollisionHandler.h"
#include "Engine.h"

CollisionHandler* CollisionHandler::sInstance = nullptr;
CollisionHandler::CollisionHandler()
{
    Engine* engine = Engine::GetInstance();

}
bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool xOverlap = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool yOverlap = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return xOverlap && yOverlap;
}
