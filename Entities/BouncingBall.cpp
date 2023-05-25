#include "BouncingBall.h"

void BouncingBall::Update(float delta)
{
	Vector2d force;
	force.X = 0.5;
	force.Y = -0.5;
	ActorRigidBody->ApplyForce(force);
	ActorRigidBody->Update(delta);
	ObjectTransform->Translate(ActorRigidBody->GetPosition());
	ActorCollider->Set((int)ObjectTransform->X, (int)ObjectTransform->Y, Width, Height);
}
