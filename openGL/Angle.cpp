
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
	rotate(p.x, p.y, cos_z, sin_z);
	rotate(p.x, p.z, cos_y, sin_y);
	rotate(p.y, p.z, cos_x, sin_x);
	return (p);
}
Point	Angle::rotate_back(Point p) const
{
	rotate(p.y, p.z, cos_x, sin_x);
	rotate(p.x, p.z, cos_y, sin_y);
	rotate(p.x, p.y, cos_z, sin_z);
	return (p);
}



void	Angle::rotate(float & pls, float & mns, float cos, float sin)
{
	float	tmp;
	tmp = pls * cos - mns * sin;
	mns = mns * cos + pls * sin;
	pls = tmp;
}
