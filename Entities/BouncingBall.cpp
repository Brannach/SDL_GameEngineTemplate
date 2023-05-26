#include "BouncingBall.h"

void BouncingBall::Update(float delta)
{
	ActorRigidBody->ApplyForce(Force);
	ActorRigidBody->Update(delta);
	LastSafePosition.X = ObjectTransform->X;
	LastSafePosition.Y = ObjectTransform->Y;
	ObjectTransform->Translate(ActorRigidBody->GetPosition());
	ActorCollider->Set((int)ObjectTransform->X, (int)ObjectTransform->Y, Width, Height);

	//Check collision with the borders or walls of the window application
	BoolPair collisionResult = CollisionHandler::GetInstance()->CheckAppWallCollision(ActorCollider->Get());
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

	//Check collision with bricks


	ActorRigidBody->Update(delta);
}
