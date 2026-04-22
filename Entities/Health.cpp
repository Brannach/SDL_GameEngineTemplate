#include "Health.h"
#include "..\Core\Engine.h"
#include "..\Rendering\TextureRenderer.h"

void Health::Update(float delta)
{
	Box box = ActorCollider.Get();
}

void Health::Draw()
{
	Box box = ActorCollider.Get();
	
	int currentHealth = Engine::GetInstance().GetGameplayRules()->GetHealth();
	for (int i = 0; i < currentHealth; i++)
	{
		box.x += box.w + 5;
		TextureRenderer::GetInstance().Draw(TextureId, box, ObjectFlip, Engine::GetInstance().GetRenderer());
	}
}
