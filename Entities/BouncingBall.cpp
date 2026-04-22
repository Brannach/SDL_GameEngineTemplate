#include "BouncingBall.h"
#include "..\Core\Engine.h"

void BouncingBall::Update(float delta)
{
	Engine& engine = Engine::GetInstance();
	TemplateGameplayRules* gameRules = engine.GetGameplayRules();
	bool hasCollision = false;
	Actor* brickToRemove = nullptr;
	
	if (gameRules->GetCurrentGameState() != Running)
	{
		IsVisible = false;
		ResetPosition();
		ResetForce();
		return;
	}
	ActorRigidBody.ApplyForce(Force);
	ActorRigidBody.Update(delta);
	LastSafePosition.X = ObjectTransform.X;
	LastSafePosition.Y = ObjectTransform.Y;
	ObjectTransform.Translate(ActorRigidBody.GetPosition());
	ActorCollider.Set((int)ObjectTransform.X, (int)ObjectTransform.Y, Width, Height);
	
	//Lose health when Y coordinate passes the Y limit
	if ((LastSafePosition.Y + Height) > gameRules->GetHealthLossLimit() - Force.Y)
	{
		ResetPosition();
		ResetForce();
		IsVisible = false;
		gameRules->DecreaseHealth(1);
		return;
	}
	IsVisible = true;
	CollisionHandler& collisionHandler = CollisionHandler::GetInstance();
	BoolPair collisionResult;

	//Check collision with bricks
	auto result = collisionHandler.CheckCollisionWithActors(
		ActorCollider.Get(), engine.GetRenderedActors(), this);

	if (result.hitActor) {
		if (result.values.X < 0) {
			ObjectTransform.X = LastSafePosition.X;
			Force.X *= -1;
		}
		if (result.values.Y < 0) {
			ObjectTransform.Y = LastSafePosition.Y;
			Force.Y *= -1;
			if (abs(result.values.X) > 20 && (result.centerDistances.X * Force.X) < 0)
				Force.X *= -1;
		}
		ActorRigidBody.Update(delta);
		if (result.hitActor->ShouldDestroyOnCollision())
			engine.RemoveRenderedActor(result.hitActor);
		return;
	}
	
	//Check collision with the walls of the window application
	collisionResult = collisionHandler.CheckAppWallCollision(ActorCollider.Get());
	if (get<0>(collisionResult))
	{
		//collision with X walls
		ObjectTransform.X = LastSafePosition.X;
		Force.X *= -1;
	}
	if (get<1>(collisionResult))
	{
		//collision with Y walls
		ObjectTransform.Y = LastSafePosition.Y;
		Force.Y *= -1;
	}

	ActorRigidBody.Update(delta);
}
