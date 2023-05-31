#include "BouncingBall.h"
#include "Engine.h"
#include <typeinfo>

void BouncingBall::Update(float delta)
{
	Engine* engine = Engine::GetInstance();
	TemplateGameplayRules* gameRules = engine->GetGameplayRules();

	if (gameRules->GetCurrentGameState() != Running)
	{
		IsVisible = false;
		ResetPosition();
		ResetForce();
		return;
	}
	ActorRigidBody->ApplyForce(Force);
	ActorRigidBody->Update(delta);
	LastSafePosition.X = ObjectTransform->X;
	LastSafePosition.Y = ObjectTransform->Y;
	ObjectTransform->Translate(ActorRigidBody->GetPosition());
	ActorCollider->Set((int)ObjectTransform->X, (int)ObjectTransform->Y, Width, Height);

	
	//Lose health when Y coordinate passes the Y limit
	if ((LastSafePosition.Y + Height) > gameRules->GetHealthLossLimit()-Force.Y)
	{
		ResetPosition();
		ResetForce();
		IsVisible = false;
		gameRules->DecreaseHealth(1);
		return;
	}
	IsVisible = true;
	CollisionHandler* collisionHandler = CollisionHandler::GetInstance();
	BoolPair collisionResult;

	//Check collision with bricks
	list<Actor*> ActorList = engine->GetRenderedActors();
	for (Actor* actor : ActorList)
	{
		if (actor->CanCollide() && actor != this)
		{
			if (collisionHandler->CheckRectCollision(ActorCollider->Get(), actor->GetCollider()->Get()))
			{
				Vector2d values = collisionHandler->GetCollisionValues(ActorCollider->Get(), actor->GetCollider()->Get());
				if (values.X < 0) {
					ObjectTransform->X = LastSafePosition.X;
					Force.X *= -1;
				}
				if (values.Y < 0)
				{
					ObjectTransform->Y = LastSafePosition.Y;
					Force.Y *= -1;
				}				
				ActorRigidBody->Update(delta);
				string classType = typeid(*actor).name();
				if (classType.find("Brick") != string::npos)
				{
					engine->RemoveRenderedActor(actor);
				}
				return;
			}
		}
	}

	//Check collision with the walls of the window application
	collisionResult = collisionHandler->CheckAppWallCollision(ActorCollider->Get());
	if (get<0>(collisionResult))
	{
		//collision with X walls
		ObjectTransform->X = LastSafePosition.X;
		Force.X *= -1;
	}
	if (get<1>(collisionResult))
	{
		//collision with Y walls
		ObjectTransform->Y = LastSafePosition.Y;
		Force.Y *= -1;
	}

	ActorRigidBody->Update(delta);
}
