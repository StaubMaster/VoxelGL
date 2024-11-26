
#include "math3D.hpp"

RayCast3D_Data	RayCast3D_init(Point pos, Point dir, float scale)
{
	RayCast3D_Data	data;

	data.scale = scale;

	data.ray_pos = pos;
	data.ray_dir = dir;

	data.norm_pos = pos / scale;
	data.grid_idx.x = (int)floor(data.norm_pos.x);
	data.grid_idx.y = (int)floor(data.norm_pos.y);
	data.grid_idx.z = (int)floor(data.norm_pos.z);
	data.norm_dir = dir / (dir.length());

	if (data.norm_dir.x != 0) { data.side_len.x = sqrt(data.norm_dir.y * data.norm_dir.y + data.norm_dir.z * data.norm_dir.z) / data.norm_dir.x; } else { data.side_len.x = 0xFFFFFFFF; }
	if (data.norm_dir.y != 0) { data.side_len.y = sqrt(data.norm_dir.z * data.norm_dir.z + data.norm_dir.x * data.norm_dir.x) / data.norm_dir.y; } else { data.side_len.y = 0xFFFFFFFF; }
	if (data.norm_dir.z != 0) { data.side_len.z = sqrt(data.norm_dir.x * data.norm_dir.x + data.norm_dir.y * data.norm_dir.y) / data.norm_dir.z; } else { data.side_len.z = 0xFFFFFFFF; }

	data.side_len.x = sqrt(1 + data.side_len.x * data.side_len.x);
	data.side_len.y = sqrt(1 + data.side_len.y * data.side_len.y);
	data.side_len.z = sqrt(1 + data.side_len.z * data.side_len.z);

	if (data.norm_dir.x > 0)
	{
		data.grid_dir.x = +1;
		data.side_sum.x = ((data.grid_idx.x + 1) - data.norm_pos.x) * data.side_len.x;
		data.cardinal_x = AXIS_BITS_XN;
	}
	else
	{
		data.grid_dir.x = -1;
		data.side_sum.x = (data.norm_pos.x - data.grid_idx.x) * data.side_len.x;
		data.cardinal_x = AXIS_BITS_XP;
	}

	if (data.norm_dir.y > 0)
	{
		data.grid_dir.y = +1;
		data.side_sum.y = ((data.grid_idx.y + 1) - data.norm_pos.y) * data.side_len.y;
		data.cardinal_y = AXIS_BITS_YN;
	}
	else
	{
		data.grid_dir.y = -1;
		data.side_sum.y = (data.norm_pos.y - data.grid_idx.y) * data.side_len.y;
		data.cardinal_y = AXIS_BITS_YP;
	}

	if (data.norm_dir.z > 0)
	{
		data.grid_dir.z = +1;
		data.side_sum.z = ((data.grid_idx.z + 1) - data.norm_pos.z) * data.side_len.z;
		data.cardinal_z = AXIS_BITS_ZN;
	}
	else
	{
		data.grid_dir.z = -1;
		data.side_sum.z = (data.norm_pos.z - data.grid_idx.z) * data.side_len.z;
		data.cardinal_z = AXIS_BITS_ZP;
	}

	return (data);
}
RayCast3D_Hit	RayCast3D_continue(RayCast3D_Data & data)
{
	RayCast3D_Hit hit;
	hit.isHit = false;

	if (data.side_sum.x < data.side_sum.y && data.side_sum.x < data.side_sum.z)
	{
		hit.t = data.side_sum.x;
		data.side_sum.x += data.side_len.x;
		data.grid_idx.x += data.grid_dir.x;
		hit.from_axis = data.cardinal_x;
	}
	else if (data.side_sum.y < data.side_sum.z && data.side_sum.y < data.side_sum.z)
	{
		hit.t = data.side_sum.y;
		data.side_sum.y += data.side_len.y;
		data.grid_idx.y += data.grid_dir.y;
		hit.from_axis = data.cardinal_y;
	}
	else
	{
		hit.t = data.side_sum.z;
		data.side_sum.z += data.side_len.z;
		data.grid_idx.z += data.grid_dir.z;
		hit.from_axis = data.cardinal_z;
	}

	return (hit);
}
RayCast3D_Hit	RayCast3D_hit(RayCast3D_Hit hit, RayCast3D_Data data)
{
	hit.isHit = true;
	hit.idx.x = data.grid_idx.x;
	hit.idx.y = data.grid_idx.y;
	hit.idx.z = data.grid_idx.z;
	hit.pos = data.ray_pos + (data.ray_dir * (hit.t * data.scale));
	hit.dir = data.ray_dir;

	Point & dir = data.ray_dir;
	Point abs_d(abs(dir.x), abs(dir.y), abs(dir.z));

	if (abs_d.x >= abs_d.y && abs_d.x >= abs_d.z)
	{
		if (dir.x < 0) { hit.dir1 = AXIS_BITS_XN; } else { hit.dir1 = AXIS_BITS_XP; }
		if (abs_d.y >= abs_d.z)
		{
			if (dir.y < 0) { hit.dir2 = AXIS_BITS_YN; } else { hit.dir2 = AXIS_BITS_YP; }
			if (dir.z < 0) { hit.dir3 = AXIS_BITS_ZN; } else { hit.dir3 = AXIS_BITS_ZP; }
		}
		else
		{
			if (dir.z < 0) { hit.dir2 = AXIS_BITS_ZN; } else { hit.dir2 = AXIS_BITS_ZP; }
			if (dir.y < 0) { hit.dir3 = AXIS_BITS_YN; } else { hit.dir3 = AXIS_BITS_YP; }
		}
	}
	else if (abs_d.y >= abs_d.x && abs_d.y >= abs_d.z)
	{
		if (dir.y < 0) { hit.dir1 = AXIS_BITS_YN; } else { hit.dir1 = AXIS_BITS_YP; }
		if (abs_d.x >= abs_d.z)
		{
			if (dir.x < 0) { hit.dir2 = AXIS_BITS_XN; } else { hit.dir2 = AXIS_BITS_XP; }
			if (dir.z < 0) { hit.dir3 = AXIS_BITS_ZN; } else { hit.dir3 = AXIS_BITS_ZP; }
		}
		else
		{
			if (dir.z < 0) { hit.dir2 = AXIS_BITS_ZN; } else { hit.dir2 = AXIS_BITS_ZP; }
			if (dir.x < 0) { hit.dir3 = AXIS_BITS_XN; } else { hit.dir3 = AXIS_BITS_XP; }
		}
	}
	else
	{
		if (dir.z < 0) { hit.dir1 = AXIS_BITS_ZN; } else { hit.dir2 = AXIS_BITS_ZP; }
		if (abs_d.x >= abs_d.y)
		{
			if (dir.x < 0) { hit.dir2 = AXIS_BITS_XN; } else { hit.dir2 = AXIS_BITS_XP; }
			if (dir.y < 0) { hit.dir3 = AXIS_BITS_YN; } else { hit.dir3 = AXIS_BITS_YP; }
		}
		else
		{
			if (dir.y < 0) { hit.dir2 = AXIS_BITS_YN; } else { hit.dir2 = AXIS_BITS_YP; }
			if (dir.x < 0) { hit.dir3 = AXIS_BITS_XN; } else { hit.dir3 = AXIS_BITS_XP; }
		}
	}

	return (hit);
}


RayCast3D_Hit	RayCast3D(
	Point pos, Point dir,
	int max_dist,
	float scale,
	const void * obj,
	int(* hit_func)(const void *, Index3D))
{
	RayCast3D_Hit hit;
	hit.from_axis = 0;
	hit.t = 0;

	RayCast3D_Data data = RayCast3D_init(pos, dir, scale);

	while (hit.t < max_dist)
	{
		int check = hit_func(obj, data.grid_idx);
		if (check < 0)
		{
			hit.isHit = false;
			return hit;
		}
		if (check > 0)
		{
			hit = RayCast3D_hit(hit, data);
			hit.pos = data.ray_pos + (data.ray_dir * hit.t);
			return hit;
		}

		hit = RayCast3D_continue(data);
	}

	hit.isHit = false;
	return hit;
}
