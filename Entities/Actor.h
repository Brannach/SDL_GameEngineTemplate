#pragma once

#include "GameObject.h"
#include "..\Physics\Collider.h"
#include "..\Physics\RigidBody.h"

class Actor : public GameObject
{
public:
	Actor();
	Actor(Properties* pr) : GameObject(pr) 
	{
		ActorCollider = new Collider();
		ActorCollider->Set((int)Origin->X, (int)Origin->Y, (int)Width, (int)Height);
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

protected:
	Collider* ActorCollider;
	RigidBody* ActorRigidBody;
};
