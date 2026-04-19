#include "Paddle.h"
#include "..\Core\EventHandler.h"

void Paddle::Update(float delta)
{
	if (Engine::GetInstance()->GetGameplayRules()->GetCurrentGameState() != Running)
	{
		IsVisible = false;
		ResetPosition();
		return;
	}
	IsVisible = true;
	EventHandler* eventHandler = EventHandler::GetInstance();

	ActorRigidBody.ResetForce();

	if (eventHandler->GetAxisKey(HORIZONTAL) == 1)
	{
		ActorRigidBody.ApplyForceX(1.0);
	}
	if (eventHandler->GetAxisKey(HORIZONTAL) == -1)
	{
		ActorRigidBody.ApplyForceX(-1.0);
	}

	LastSafePosition.X = ObjectTransform->X;
	ObjectTransform->Translate(ActorRigidBody.GetPosition());
	ActorCollider.Set((int)ObjectTransform->X, (int)ObjectTransform->Y, Width, Height);

	BoolPair collisionResult = CollisionHandler::GetInstance()->CheckAppWallCollision(ActorCollider.Get());
	if (get<0>(collisionResult))
	{
		//collision with X walls
		ObjectTransform->X = LastSafePosition.X;
		Force.X *= 0;
	}
	ActorRigidBody.Update(delta);
}
