#pragma once

#include <memory>

#include "GameObject.h"
#include "..\Physics\Collider.h"
#include "..\Physics\RigidBody.h"

class Actor : public GameObject
{
public:
	Actor();
	Actor(const Properties& pr) : GameObject(pr) 
	{
		ActorCollider = Collider();
		ActorCollider.Set((int)Origin.X, (int)Origin.Y, (int)Width, (int)Height);
		ActorCollider.SetBuffer(0, 0, 0, 0);

		ActorRigidBody = RigidBody();
		ActorRigidBody.SetGravity(DEFAULT_GRAVITY);
	};
	
	~Actor() = default;

	virtual void Draw();
	virtual void Update(float delta);
	virtual void Clean();
	virtual void DrawCollisorBox();
	inline RigidBody GetRigidBody() { return ActorRigidBody; }
	inline Collider GetCollider() { return ActorCollider; }

protected:
	Collider ActorCollider;
	RigidBody ActorRigidBody;
};
