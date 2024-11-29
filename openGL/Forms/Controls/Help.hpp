
#pragma once
#include <iostream>

struct	Point2D
{
	float	X;
	float	Y;

	Point2D();
	Point2D(float x, float y);
};

struct	Color
{
	float	R;
	float	G;
	float	B;

	Color(float r, float g, float b);
};

struct	Box2D
{
	Point2D	Min;
	Point2D	Max;

	Box2D();
	Box2D(float x1, float y1, float x2, float y2);
	Box2D(Point2D p1, Point2D p2);

	bool	check(Point2D p);
};





struct FormControlRenderData
{
	Box2D	Box;
	Color	Col;
	float	Depth;
};
