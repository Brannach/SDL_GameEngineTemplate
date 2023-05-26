#include "BouncingBall.h"
#include "Engine.h"
#include <typeinfo>
void BouncingBall::Update(float delta)
{
	ActorRigidBody->ApplyForce(Force);
	ActorRigidBody->Update(delta);
	LastSafePosition.X = ObjectTransform->X;
	LastSafePosition.Y = ObjectTransform->Y;
	ObjectTransform->Translate(ActorRigidBody->GetPosition());
	ActorCollider->Set((int)ObjectTransform->X, (int)ObjectTransform->Y, Width, Height);

	CollisionHandler* collisionHandler = CollisionHandler::GetInstance();
	BoolPair collisionResult;
	//Check collision with bricks
	list<Actor*> ActorList = Engine::GetInstance()->GetRenderedActors();
	for (Actor* actor : ActorList)
	{
		string classType = typeid(*actor).name();
		if (classType.find("Brick") != string::npos || classType.find("Paddle") != string::npos)
		{
			if (collisionHandler->CheckRectCollision(ActorCollider->Get(), actor->GetCollider()->Get()))
			{
				//collision with X walls
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
				return;
			}
		}
	}

	//Check collision with the borders or walls of the window application
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
