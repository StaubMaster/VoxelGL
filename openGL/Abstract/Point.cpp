
#include "Point.hpp"

Point::Point() : x(0), y(0), z(0)
{

}
Point::Point(float x, float y, float z) : x(x), y(y), z(z)
{

}
Point::~Point()
{

}
Point::Point(const Point & other) : x(other.x), y(other.y), z(other.z)
{

}
const Point & Point::operator =(const Point & other)
{
	this -> x = other.x;
	this -> y = other.y;
	this -> z = other.z;
	return *this;
}



Point Point::operator +(const Point & other) const
{
	return Point(
		x + other.x,
		y + other.y,
		z + other.z
	);
}
Point Point::operator -(const Point & other) const
{
	return Point(
		x - other.x,
		y - other.y,
		z - other.z
	);
}
Point Point::operator *(const Point & other) const
{
	return Point(
		x * other.x,
		y * other.y,
		z * other.z
	);
}
Point Point::operator /(const Point & other) const
{
	return Point(
		x / other.x,
		y / other.y,
		z / other.z
	);
}

Point Point::operator *(const float & flt) const
{
	return Point(
		x * flt,
		y * flt,
		z * flt
	);
}
Point Point::operator /(const float & flt) const
{
	return Point(
		x / flt,
		y / flt,
		z / flt
	);
}

float Point::length() const
{
	return sqrt(
		(x * x) +
		(y * y) +
		(z * z)
	);
}



Point	Point::Sign() const
{
	Point p;

	if (x > 0) { p.x = +1; }
	if (x < 0) { p.x = -1; }

	if (y > 0) { p.y = +1; }
	if (y < 0) { p.y = -1; }

	if (z > 0) { p.z = +1; }
	if (z < 0) { p.z = -1; }

	return (p);
}

Point	Point::Magnitude_Min() const
{
	Point mag(abs(x), abs(y), abs(z));

	if (mag.x <= mag.y && mag.x <= mag.z)
		return (Point(x, 0, 0));
	if (mag.y <= mag.z && mag.y <= mag.x)
		return (Point(0, y, 0));
	if (mag.z <= mag.x && mag.z <= mag.y)
		return (Point(0, 0, z));

	return (Point());
}





std::ostream & operator <<(std::ostream & o, const Point & p)
{
	o << p.x << ":" << p.y << ":" << p.z;
	return o;
}
