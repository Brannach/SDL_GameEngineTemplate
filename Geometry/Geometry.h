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