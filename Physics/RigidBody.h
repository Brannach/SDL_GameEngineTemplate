#pragma once

#include "Geometry2d.h"

#define UNIT_MASS		1.0f
#define DEFAULT_GRAVITY	1.0f

class RigidBody
{
public:
	RigidBody()
	{
		mMass = UNIT_MASS;
		mGravity = DEFAULT_GRAVITY;
	}

	inline void SetMass(float mass) { mMass = mass; }
	inline void SetGravity(float grav) { mGravity = grav; }

	inline void ApplyForce(Vector2d force) { mForce = force; }
	inline void ApplyForceX(float forceX) { mForce.X = forceX; }
	inline void ApplyForceY(float forceY) { mForce.Y = forceY; }
	inline void ResetForce() { mForce = Vector2d(0, 0); }

	inline void ApplyFriction(Vector2d fric) { mFriction = fric; }
	inline void ApplyFrictionX(float fricX) { mFriction.X = fricX; }
	inline void ApplyFrictionY(float fricY) { mFriction.Y = fricY; }
	inline void ResetFriction() { mFriction = Vector2d(0, 0); }

	inline void SetPosition(Vector2d pos) { mPosition = pos; }
	inline void SetVelocity(Vector2d vel) { mVelocity = vel; }
	inline void SetAcceleration(Vector2d acc) { mAcceleration = acc; }

	inline float GetMass() { return mMass; }
	inline Vector2d GetPosition() { return mPosition; }
	inline Vector2d GetAcceleration() { return mAcceleration; }
	inline Vector2d GetVelocity() { return mVelocity; }
	inline Vector2d GetDeltaPos() { return mDeltaPos; }

	void Update(float delta)
	{
		mAcceleration.X = (mForce.X + mFriction.X) / mMass;
		mAcceleration.Y = (mForce.Y + mGravity) / mMass;
		mVelocity = mAcceleration * delta;
		mDeltaPos = mPosition - (mVelocity * delta);
		mPosition = mVelocity * delta;
	}

private:
	float mMass;
	float mGravity;

	Vector2d mForce;
	Vector2d mFriction;
	Vector2d mPosition;
	Vector2d mVelocity;
	Vector2d mAcceleration;
	Vector2d mDeltaPos;
};

