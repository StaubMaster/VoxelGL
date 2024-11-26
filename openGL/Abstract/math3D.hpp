
#ifndef MATH3D_H
# define MATH3D_H
# include <math.h>

# include "Point.hpp"
# include "Angle.hpp"
# include "Index3D.hpp"
# include "Undex3D.hpp"

# define AXIS_BITS_XN 0b001
# define AXIS_BITS_XP 0b110
# define AXIS_BITS_YN 0b010
# define AXIS_BITS_YP 0b101
# define AXIS_BITS_ZN 0b100
# define AXIS_BITS_ZP 0b011

struct	RayCast3D_Data
{
	float	scale;
	Point	ray_pos;
	Point	ray_dir;

	Point	norm_pos;
	Point	norm_dir;

	Index3D	grid_idx;
	Index3D	grid_dir;

	Point	side_len;
	Point	side_sum;

	char	cardinal_x;
	char	cardinal_y;
	char	cardinal_z;
};

struct	RayCast3D_Hit
{
	bool	isHit;

	Index3D	idx;

	char	from_axis;

	Point	dir;
	char	dir1;
	char	dir2;
	char	dir3;

	float	t;
	Point	pos;
};

RayCast3D_Data	RayCast3D_init(Point pos, Point dir, float scale);
RayCast3D_Hit	RayCast3D_continue(RayCast3D_Data & data);
RayCast3D_Hit	RayCast3D_hit(RayCast3D_Hit hit, RayCast3D_Data data);

RayCast3D_Hit	RayCast3D(
	Point pos, Point dir,
	int max_dist,
	float scale,
	const void * obj,
	int(* hit_func)(const void *, Index3D));

RayCast3D_Hit	RayCast3D_Recursive(
	Point pos, Point dir,
	int max_dist,
	const void * obj,
	void * obj_hit,
	int(* hit_func)(const void *, void *, Index3D, Point, Point));

#endif
