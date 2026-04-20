#pragma once

#include "..\Geometry\Transform2d.h"
#include "..\Physics\CollisionHandler.h"

#include <SDL.h>

#include <string>
#include <list>

using namespace std;

struct Properties
{
public:
	Properties(string textureId, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		X = x;
		Y = y;
		Flip = flip;
		Width = width;
		Height = height;
		TextureId = textureId;
	}
	string TextureId;
	int Width, Height;
	float X, Y;
	SDL_RendererFlip Flip;
};

class GameObject
{
public:
	GameObject() { Height = 0; Width = 0; ObjectTransform = Transform2d(); }
	GameObject(const Properties& pr)
	{
		TextureId = pr.TextureId;
		Width = pr.Width;
		Height = pr.Height;
		ObjectFlip = pr.Flip;
		ObjectTransform = Transform2d(pr.X, pr.Y);
		Origin = Point2d();
		Origin.X = pr.X;
		Origin.Y = pr.Y;
	};
	~GameObject() = default;

	inline Point2d GetOrigin() { return Origin; }
	virtual void Draw() = 0;
	virtual void DrawCollisorBox() = 0;
	virtual void Update(float delta) = 0;
	virtual void Clean() = 0;
	inline Transform2d GetTransform() { return ObjectTransform; }
	inline bool CanCollide() { return HasCollision; }
	inline void ResetPosition() { ObjectTransform = Transform2d(Origin.X, Origin.Y); }

protected:
	Point2d Origin;
	Transform2d ObjectTransform;
	int Width, Height;
	string TextureId;
	SDL_RendererFlip ObjectFlip;
	Vector2d LastSafePosition;
	bool HasCollision = true;
	bool IsVisible = true;
};

