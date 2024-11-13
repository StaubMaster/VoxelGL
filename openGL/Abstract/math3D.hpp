
#ifndef MATH3D_H
# define MATH3D_H
# include "Point.hpp"
# include "Angle.hpp"

# define CARDINAL_X_NEGATIVE 1
# define CARDINAL_X_POSITIVE 2
# define CARDINAL_Y_NEGATIVE 3
# define CARDINAL_Y_POSITIVE 4
# define CARDINAL_Z_NEGATIVE 5
# define CARDINAL_Z_POSITIVE 6

struct	Index3D
{
	int	x;
	int	y;
	int	z;
};
struct	Undex3D
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
};

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
	char	cardinal;

	float	t;
	Point	pos;
};

RayCast3D_Data	RayCast3D_init(Point pos, Point dir, float scale);
RayCast3D_Hit	RayCast3D_continue(RayCast3D_Data & data);
RayCast3D_Hit	RayCast3D_hit(RayCast3D_Hit hit, RayCast3D_Data data);

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
