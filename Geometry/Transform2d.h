#pragma once

#include "Geometry2d.h"

class Transform2d
{
public:
	float X, Y;

	Transform2d(float x = 0, float y = 0) : X(x), Y(y) {}

	inline void TranslateX(float scalar) { X += scalar; }
	inline void TranslateY(float scalar) { Y += scalar; }
	inline void Translate(Vector2d v1) { X += v1.X; Y += v1.Y; }
};