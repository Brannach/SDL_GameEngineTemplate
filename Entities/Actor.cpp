#include "Actor.h"
#include "Engine.h"

Actor::Actor()
{
}

void Actor::Draw()
{
	Box box = ActorCollider->Get();
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 100, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Actor::Update(float delta)
{
}

void Actor::Clean()
{
}
