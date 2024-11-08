
#include "math3D.hpp"

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





void	rotate_fore(float *pls, float *mns, float cos, float sin)
{
	float	temppp;
	temppp = pls[0] * cos - mns[0] * sin;
	mns[0] = mns[0] * cos + pls[0] * sin;
	pls[0] = temppp;
}
void	rotate_back(float *pls, float *mns, float cos, float sin)
{
	float	temppp;
	temppp = pls[0] * cos + mns[0] * sin;
	mns[0] = mns[0] * cos - pls[0] * sin;
	pls[0] = temppp;
}

