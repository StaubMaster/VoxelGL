
#ifndef POINT_HPP
# define POINT_HPP
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

#endif
