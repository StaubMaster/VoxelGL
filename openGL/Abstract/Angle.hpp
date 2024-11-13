
#ifndef ANGLE_HPP
# define ANGLE_HPP
# include <math.h>
# include "Point.hpp"

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

		Angle	rotate_fore(Angle a) const;
		Angle	rotate_back(Angle a) const;

	public:
		static void	rotate(float & pls, float & mns, float cos, float sin);
};

#endif
