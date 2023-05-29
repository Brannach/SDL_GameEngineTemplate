#pragma once

#include "Transform2d.h"
#include "CollisionHandler.h"

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
	GameObject() { Height = 0; Width = 0; ObjectTransform = nullptr; }
	GameObject(Properties* pr)
	{
		TextureId = pr->TextureId;
		Width = pr->Width;
		Height = pr->Height;
		ObjectFlip = pr->Flip;
		ObjectTransform = new Transform2d(pr->X, pr->Y);

		Origin = new Point2d();
		Origin->X = pr->X;// +pr->Width / 2;
		Origin->Y = pr->Y;// +pr->Height / 2;
	};

	inline Point2d* GetOrigin() { return Origin; }
	virtual void Draw() = 0;
	virtual void DrawCollisorBox() = 0;
	virtual void Update(float delta) = 0;
	virtual void Clean() = 0;
	inline Transform2d* GetTransform() { return ObjectTransform; }

protected:
	Point2d* Origin;
	Transform2d* ObjectTransform;
	int Width, Height;
	string TextureId;
	SDL_RendererFlip ObjectFlip;
	Vector2d LastSafePosition;
};

