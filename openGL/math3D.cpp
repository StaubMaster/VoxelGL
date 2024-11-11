
#include "math3D.hpp"


/// @brief like ray-casting but in 3D
/// @param checkfunc should return >0 if hit is found, <0 if search should stop, and =0 if search should continue
/// @return hit
VoxelHit	VoxelCross(Point pos, Point dir, const void * p, int(* checkfunc)(const void *, int, int, int), int max_dist)
{
	VoxelHit hit;
	hit.isHit = false;

	dir.x = -dir.x;
	dir.y = -dir.y;

	Point ray_pos = pos;
	Point ray_dir = dir;

	int	ray_grid_idx_x = (int)pos.x;
	int	ray_grid_idx_y = (int)pos.y;
	int	ray_grid_idx_z = (int)pos.z;
	dir = dir / (dir.length());

	float	ray_side_len_x;
	float	ray_side_len_y = 0;
	float	ray_side_len_z;

	if (dir.x != 0) { ray_side_len_x = sqrt(dir.y * dir.y + dir.z * dir.z) / dir.x; } else { ray_side_len_x = 0xFFFFFFFF; }
	if (dir.y != 0) { ray_side_len_y = sqrt(dir.z * dir.z + dir.x * dir.x) / dir.y; } else { ray_side_len_y = 0xFFFFFFFF; }
	if (dir.z != 0) { ray_side_len_z = sqrt(dir.x * dir.x + dir.y * dir.y) / dir.z; } else { ray_side_len_z = 0xFFFFFFFF; }

	ray_side_len_x = sqrt(1 + ray_side_len_x * ray_side_len_x);
	ray_side_len_y = sqrt(1 + ray_side_len_y * ray_side_len_y);
	ray_side_len_z = sqrt(1 + ray_side_len_z * ray_side_len_z);

	float ray_sum = 0;



	int	ray_grid_dir_x;
	int	ray_grid_dir_y;
	int	ray_grid_dir_z;

	float	ray_side_sum_x;
	float	ray_side_sum_y;
	float	ray_side_sum_z;

	int	ray_cardinal_side_x;
	int	ray_cardinal_side_y;
	int	ray_cardinal_side_z;

	if (dir.x > 0)
	{
		ray_grid_dir_x = +1;
		ray_side_sum_x = ((ray_grid_idx_x + 1) - pos.x) * ray_side_len_x;
		ray_cardinal_side_x = 1;
	}
	else
	{
		ray_grid_dir_x = -1;
		ray_side_sum_x = (pos.x - ray_grid_idx_x) * ray_side_len_x;
		ray_cardinal_side_x = 2;
	}

	if (dir.y > 0)
	{
		ray_grid_dir_y = +1;
		ray_side_sum_y = ((ray_grid_idx_y + 1) - pos.y) * ray_side_len_y;
		ray_cardinal_side_y = 3;
	}
	else
	{
		ray_grid_dir_y = -1;
		ray_side_sum_y = (pos.y - ray_grid_idx_y) * ray_side_len_y;
		ray_cardinal_side_y = 4;
	}

	if (dir.z > 0)
	{
		ray_grid_dir_z = +1;
		ray_side_sum_z = ((ray_grid_idx_z + 1) - pos.z) * ray_side_len_z;
		ray_cardinal_side_z = 5;
	}
	else
	{
		ray_grid_dir_z = -1;
		ray_side_sum_z = (pos.z - ray_grid_idx_z) * ray_side_len_z;
		ray_cardinal_side_z = 6;
	}

	int	ray_cardinal_dir = 0;



	while (ray_sum < max_dist)
	{
		int check = checkfunc(p, ray_grid_idx_x, ray_grid_idx_y, ray_grid_idx_z);
		if (check < 0)
		{
			return hit;
		}
		if (check > 0)
		{
			hit.isHit = true;
			hit.x = ray_grid_idx_x;
			hit.y = ray_grid_idx_y;
			hit.z = ray_grid_idx_z;
			hit.t = ray_sum;
			hit.pos = ray_pos + (ray_dir * hit.t);
			return hit;
		}

		if (ray_side_sum_x < ray_side_sum_y && ray_side_sum_x < ray_side_sum_z)
		{
			ray_sum = ray_side_sum_x;
			ray_side_sum_x += ray_side_len_x;
			ray_grid_idx_x += ray_grid_dir_x;
			ray_cardinal_dir = ray_cardinal_side_x;
		}
		else if (ray_side_sum_y < ray_side_sum_z && ray_side_sum_y < ray_side_sum_z)
		{
			ray_sum = ray_side_sum_y;
			ray_side_sum_y += ray_side_len_y;
			ray_grid_idx_y += ray_grid_dir_y;
			ray_cardinal_dir = ray_cardinal_side_y;
		}
		else
		{
			ray_sum = ray_side_sum_z;
			ray_side_sum_z += ray_side_len_z;
			ray_grid_idx_z += ray_grid_dir_z;
			ray_cardinal_dir = ray_cardinal_side_z;
		}
	}
	return hit;
}
