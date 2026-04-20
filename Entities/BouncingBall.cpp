#include "BouncingBall.h"
#include "..\Core\Engine.h"
#include <typeinfo>

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
	const auto& ActorList = engine.GetRenderedActors();
	for (const auto& actor : ActorList)
	{
		if (actor->CanCollide() && actor.get() != this)
		{
			if (collisionHandler.CheckRectCollision(ActorCollider.Get(), actor->GetCollider().Get()))
			{
				Vector2d centerValues;

				Vector2d values = collisionHandler.GetCollisionValues(ActorCollider.Get(), actor->GetCollider().Get(), centerValues);
				if (values.X < 0) {
					ObjectTransform.X = LastSafePosition.X;
					Force.X *= -1;
				}
				if (values.Y < 0)
				{
					ObjectTransform.Y = LastSafePosition.Y;
					Force.Y *= -1;
					if ((abs(values.X) > 20))
					{
						if ((centerValues.X * Force.X) < 0)
						{
							Force.X *= -1;
						}
					}
				}				
				ActorRigidBody.Update(delta);
				string classType = typeid(*actor).name();
				if (classType.find("Brick") != string::npos)
				{
					brickToRemove = actor.get();					
				}
				hasCollision = true;
				break;
			}			
		}
	}

	if (brickToRemove)
		engine.RemoveRenderedActor(brickToRemove);
	if (hasCollision)
		return;
	
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
