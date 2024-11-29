
#include "Help.hpp"

Point2D::Point2D() : X(0), Y(0) { }
Point2D::Point2D(float x, float y) : X(x), Y(y) { }

Color::Color(float r, float g, float b) : R(r), G(g), B(b) { }

Box2D::Box2D() : Min(), Max() { }
Box2D::Box2D(float x1, float y1, float x2, float y2)
{
	Min.X = std::min(x1, x2);
	Min.Y = std::min(y1, y2);
	Max.X = std::max(x1, x2);
	Max.Y = std::max(y1, y2);
}
Box2D::Box2D(Point2D p1, Point2D p2)
{
	Min.X = std::min(p1.X, p2.X);
	Min.Y = std::min(p1.Y, p2.Y);
	Max.X = std::max(p1.X, p2.X);
	Max.Y = std::max(p1.Y, p2.Y);
}
bool	Box2D::check(Point2D p)
{
	return (Min.X < p.X && p.X < Max.X && 
			Min.Y < p.Y && p.Y < Max.Y
	);
}
