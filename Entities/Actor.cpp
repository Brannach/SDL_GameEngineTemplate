#include "Actor.h"
#include "Engine.h"
#include "TextureRenderer.h"

Actor::Actor()
{
}

void Actor::DrawCollisorBox()
{
	Box box = ActorCollider->Get();
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 100, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Actor::Draw()
{
	Box box = ActorCollider->Get();
	TextureRenderer::GetInstance()->Draw(TextureId, box, ObjectFlip, Engine::GetRenderer());
}

void Actor::Update(float delta)
{
}

void Actor::Clean()
{
}
