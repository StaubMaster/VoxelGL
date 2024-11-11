
#ifndef MATH3D_H
# define MATH3D_H
# include "Point.hpp"
# include "Angle.hpp"

struct	RayCast3DHit
{
	bool	isHit;

	unsigned int x;
	unsigned int y;
	unsigned int z;

	float	t;
	Point	pos;
};

/*
	pos, dir				: for th ray
	max_dist				: as a upper limit

	obj						: the object that should be raycast
	hit						: a pointer to a seperate hit object
	hitfunc					: a function what takes obj and xyz to determin weather to stop or continue searching

	return hit				: return a hit to indicate where / how far something was hit
*/
/*
	hit func needs:
		pointer to the object to check
		pointer to seperate hit object
		xyz
		pos and dir of ray
*/

RayCast3DHit	RayCast3D(Point pos, Point dir, const void * obj, int(* hitfunc)(const void *, int, int, int), int max_dist = 128);

#endif
