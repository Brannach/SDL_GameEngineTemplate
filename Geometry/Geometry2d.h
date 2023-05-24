#pragma once

using namespace std;

template<typename T> struct Dimension2d 
{
public:
	Dimension2d() { width = 0; height = 0; };
	Dimension2d(T aWidth, T aHeight)
	{
		width = aWidth;
		height = aHeight;
	};

	T width;
	T height;
};

class Vector2d
{
public:
	float X, Y;

	Vector2d(float x = 0, float y = 0) : X(x), Y(y) {}

	inline Vector2d operator+(const Vector2d& v2)
	{
		return Vector2d(X + v2.X, Y + v2.Y);
	}

	inline Vector2d operator-(const Vector2d& v2)
	{
		return Vector2d(X - v2.X, Y - v2.Y);
	}

	inline Vector2d operator*(const float scalar)
	{
		return Vector2d(X * scalar, Y * scalar);
	}

};

class Point2d
{
public:
	float X, Y;

	inline Point2d operator+(const Point2d& p2) const
	{
		return Point2d(X + p2.X, Y + p2.Y);
	}

	inline friend Point2d operator+=(Point2d& p1, const Point2d& p2)
	{
		p1.X += p2.X;
		p1.Y += p2.Y;
	}

	inline Point2d operator-(Point2d& p1) const
	{
		return Point2d(X - p1.X, Y - p1.Y);
	}

	inline friend Point2d operator-=(Point2d& p1, const Point2d& p2)
	{
		p1.X -= p2.X;
		p1.Y -= p2.Y;
	}

	inline Point2d operator*(const float scalar) const
	{
		return Point2d(X * scalar, Y * scalar);
	}
};
