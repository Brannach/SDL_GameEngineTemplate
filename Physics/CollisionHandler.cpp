#include "CollisionHandler.h"
#include "Engine.h"
#include "MainApplication.h"

using namespace std;

CollisionHandler* CollisionHandler::CollisionHandlerInstance = nullptr;

CollisionHandler::CollisionHandler()
{
    Engine* engine = Engine::GetInstance();

}
BoolPair CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    bool xOverlap = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool yOverlap = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return make_tuple(xOverlap, yOverlap);
}

BoolPair CollisionHandler::CheckAppWallCollision(SDL_Rect object)
{

    bool xOverlap = (object.x < 0) || (object.x + object.w > DEFAULT_SCREEN_WIDTH);
    bool yOverlap = (object.y < 0) || (object.y + object.h > DEFAULT_SCREEN_HEIGTH);
    return make_tuple(xOverlap, yOverlap);
}
