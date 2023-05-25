#pragma once

#include "GameObject.h"
#include "Collider.h"
#include "RigidBody.h"

class Actor : GameObject
{
public:
	Actor();
	Actor(Properties* pr) : GameObject(pr) 
	{
		ActorCollider = new Collider();
		ActorCollider->Set(Origin->X, Origin->Y, Width, Height);
		ActorCollider->SetBuffer(0, 0, 0, 0);

		ActorRigidBody = new RigidBody();
		ActorRigidBody->SetGravity(DEFAULT_GRAVITY);
	};

	virtual void Draw();
	virtual void Update(float delta);
	virtual void Clean();
	virtual void DrawCollisorBox();
	inline RigidBody* GetRigidBody() { return ActorRigidBody; }
	inline Collider* GetCollider() { return ActorCollider; }

private:
	Collider* ActorCollider;
	RigidBody* ActorRigidBody;
};
