
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
};

void	rotate_fore(float *pls, float *mns, float cos, float sin);
void	rotate_back(float *pls, float *mns, float cos, float sin);

#endif
