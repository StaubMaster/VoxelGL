
#ifndef MATH3D_H
# define MATH3D_H
# include "Point.hpp"
# include "Angle.hpp"

struct	VoxelHit
{
	bool	isHit;

	unsigned int x;
	unsigned int y;
	unsigned int z;

	float	t;
	Point	pos;
};

VoxelHit	VoxelCross(Point pos, Point dir, const void * p, int(* checkfunc)(const void *, int, int, int), int max_dist = 128);

#endif
