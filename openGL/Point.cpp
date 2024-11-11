
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
