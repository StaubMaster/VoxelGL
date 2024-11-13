
#include "Angle.hpp"

Angle::Angle() : x(0), y(0), z(0)
{
	sin_x = sin(x);
	sin_y = sin(y);
	sin_z = sin(z);
	cos_x = cos(x);
	cos_y = cos(y);
	cos_z = cos(z);
}
Angle::Angle(float x, float y, float z) : x(x), y(y), z(z)
{
	sin_x = sin(x);
	sin_y = sin(y);
	sin_z = sin(z);
	cos_x = cos(x);
	cos_y = cos(y);
	cos_z = cos(z);
}
Angle::~Angle()
{

}
Angle::Angle(const Angle & other) : x(other.x), y(other.y), z(other.z)
{
	sin_x = sin(x);
	sin_y = sin(y);
	sin_z = sin(z);
	cos_x = cos(x);
	cos_y = cos(y);
	cos_z = cos(z);
}
const Angle & Angle::operator =(const Angle & other)
{
	this -> x = other.x;
	this -> y = other.y;
	this -> z = other.z;
	this -> sin_x = other.sin_x;
	this -> sin_y = other.sin_y;
	this -> sin_z = other.sin_z;
	this -> cos_x = other.cos_x;
	this -> cos_y = other.cos_y;
	this -> cos_z = other.cos_z;
	return *this;
}



void Angle::UpdateSinCos()
{
	sin_x = sin(x);
	sin_y = sin(y);
	sin_z = sin(z);
	cos_x = cos(x);
	cos_y = cos(y);
	cos_z = cos(z);
}



Point	Angle::rotate_fore(Point p) const
{
	rotate(p.x, p.z, cos_x, sin_x);
	rotate(p.y, p.z, cos_y, sin_y);
	rotate(p.y, p.x, cos_z, sin_z);
	return (p);
}
Point	Angle::rotate_back(Point p) const
{
	rotate(p.x, p.y, cos_z, sin_z);
	rotate(p.z, p.y, cos_y, sin_y);
	rotate(p.z, p.x, cos_x, sin_x);
	return (p);
}

Angle	Angle::rotate_fore(Angle a) const
{
	Point pX, pY, pZ;
	pX = a.rotate_fore(rotate_fore(Point(1, 0, 0)));
	pY = a.rotate_fore(rotate_fore(Point(0, 1, 0)));
	pZ = a.rotate_fore(rotate_fore(Point(0, 0, 1)));

	return Angle(
		atan2f(pX.z, pZ.z),
		asinf(pY.z),
		atan2(pY.x, pY.y)
	);
}
Angle	Angle::rotate_back(Angle a) const
{
	Point pX, pY, pZ;
	pX = a.rotate_back(rotate_back(Point(1, 0, 0)));
	pY = a.rotate_back(rotate_back(Point(0, 1, 0)));
	pZ = a.rotate_back(rotate_back(Point(0, 0, 1)));

	return Angle(
		atan2f(pZ.x, pZ.z),
		asinf(pZ.y),
		atan2(pX.y, pY.y)
	);
}


void	Angle::rotate(float & pls, float & mns, float cos, float sin)
{
	float	tmp;
	tmp = pls * cos - mns * sin;
	mns = mns * cos + pls * sin;
	pls = tmp;
}
