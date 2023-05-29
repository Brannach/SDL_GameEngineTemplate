#include "Brick.h"

void Brick::Update(float delta)
{

}

void Brick::Draw()
{
	if (BrickColor.a != 0)
	{
		Box box = ActorCollider->Get();
		SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), BrickColor.r, BrickColor.g, BrickColor.b, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &box);
	}
	else Actor::Draw();
}
