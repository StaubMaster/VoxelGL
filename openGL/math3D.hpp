
#ifndef MATH3D_H
# define MATH3D_H
# include <math.h>

class Point
{
	public:
		float	x;
		float	y;
		float	z;

	public:
		Point();
		Point(float x, float y, float z);
		~Point();
		Point(const Point & other);
		const Point & operator =(const Point & other);

		Point operator +(const Point & other) const;
		Point operator -(const Point & other) const;
		Point operator *(const Point & other) const;
		Point operator /(const Point & other) const;

		Point operator *(const float & flt) const;
		Point operator /(const float & flt) const;

		float operator %(const Point & other) const;	//	scalar Product
		Point operator ^(const Point & other) const;	//	cross Product
		float length() const;
};
class Angle
{
	public:
		float	sin_x;
		float	sin_y;
		float	sin_z;
		float	cos_x;
		float	cos_y;
		float	cos_z;
		float	x;
		float	y;
		float	z;

	public:
		Angle();
		Angle(float x, float y, float z);
		~Angle();
		Angle(const Angle & other);
		const Angle & operator =(const Angle & other);

	public:
		void UpdateSinCos();

		Point	rotate_fore(Point p) const;
		Point	rotate_back(Point p) const;
};

void	rotate(float & pls, float & mns, float cos, float sin);

#endif
