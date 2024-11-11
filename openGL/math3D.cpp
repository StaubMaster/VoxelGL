
#include "math3D.hpp"

RayCast3D_Data	RayCast3D_init(Point pos, Point dir)
{
	RayCast3D_Data	data;

	dir.x = -dir.x;
	dir.y = -dir.y;

	data.grid_idx.x = (int)pos.x;
	data.grid_idx.y = (int)pos.y;
	data.grid_idx.z = (int)pos.z;
	dir = dir / (dir.length());

	if (dir.x != 0) { data.side_len.x = sqrt(dir.y * dir.y + dir.z * dir.z) / dir.x; } else { data.side_len.x = 0xFFFFFFFF; }
	if (dir.y != 0) { data.side_len.y = sqrt(dir.z * dir.z + dir.x * dir.x) / dir.y; } else { data.side_len.y = 0xFFFFFFFF; }
	if (dir.z != 0) { data.side_len.z = sqrt(dir.x * dir.x + dir.y * dir.y) / dir.z; } else { data.side_len.z = 0xFFFFFFFF; }

	data.side_len.x = sqrt(1 + data.side_len.x * data.side_len.x);
	data.side_len.y = sqrt(1 + data.side_len.y * data.side_len.y);
	data.side_len.z = sqrt(1 + data.side_len.z * data.side_len.z);

	if (dir.x > 0)
	{
		data.grid_dir.x = +1;
		data.side_sum.x = ((data.grid_idx.x + 1) - pos.x) * data.side_len.x;
		data.cardinal_x = 1;
	}
	else
	{
		data.grid_dir.x = -1;
		data.side_sum.x = (pos.x - data.grid_idx.x) * data.side_len.x;
		data.cardinal_x = 2;
	}

	if (dir.y > 0)
	{
		data.grid_dir.y = +1;
		data.side_sum.y = ((data.grid_idx.y + 1) - pos.y) * data.side_len.y;
		data.cardinal_y = 3;
	}
	else
	{
		data.grid_dir.y = -1;
		data.side_sum.y = (pos.y - data.grid_idx.y) * data.side_len.y;
		data.cardinal_y = 4;
	}

	if (dir.z > 0)
	{
		data.grid_dir.z = +1;
		data.side_sum.z = ((data.grid_idx.z + 1) - pos.z) * data.side_len.z;
		data.cardinal_z = 5;
	}
	else
	{
		data.grid_dir.z = -1;
		data.side_sum.z = (pos.z - data.grid_idx.z) * data.side_len.z;
		data.cardinal_z = 6;
	}

	data.ray_pos = pos;
	data.ray_dir = dir;
	//data.ray_dir = Point(-dir.x, -dir.y, +dir.z);

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
		hit.cardinal = data.cardinal_x;
	}
	else if (data.side_sum.y < data.side_sum.z && data.side_sum.y < data.side_sum.z)
	{
		hit.t = data.side_sum.y;
		data.side_sum.y += data.side_len.y;
		data.grid_idx.y += data.grid_dir.y;
		hit.cardinal = data.cardinal_y;
	}
	else
	{
		hit.t = data.side_sum.z;
		data.side_sum.z += data.side_len.z;
		data.grid_idx.z += data.grid_dir.z;
		hit.cardinal = data.cardinal_z;
	}

	return (hit);
}
RayCast3D_Hit	RayCast3D_hit(RayCast3D_Hit hit, RayCast3D_Data data)
{
	hit.isHit = true;
	hit.idx.x = data.grid_idx.x;
	hit.idx.y = data.grid_idx.y;
	hit.idx.z = data.grid_idx.z;
	hit.pos = data.ray_pos + (data.ray_dir * hit.t);
	return (hit);
}


RayCast3D_Hit	RayCast3D(
	Point pos, Point dir,
	int max_dist,
	const void * obj,
	int(* hit_func)(const void *, Index3D))
{
	RayCast3D_Hit hit;
	hit.cardinal = 0;
	hit.t = 0;

	RayCast3D_Data data = RayCast3D_init(pos, dir);

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

/*RayCast3D_Hit	RayCast3D_Recursive(
	Point pos, Point dir,
	int max_dist,
	const void * obj,
	void * obj_hit,
	int(* hit_func)(const void *, void *, Index3D, Point, Point))
{
	RayCast3D_Hit hit;
	hit.cardinal = 0;
	hit.t = 0;

	dir.x = -dir.x;
	dir.y = -dir.y;

	Point ray_pos = pos;
	Point ray_dir = dir;

	RayCast3D_Data data = RayCast3D_init(pos, dir);

	while (hit.t < max_dist)
	{
		hit.pos = ray_pos + (ray_dir * hit.t);
		int check = hit_func(obj, obj_hit, data.grid_idx, hit.pos, ray_dir);
		if (check < 0)
		{
			hit.isHit = false;
			return hit;
		}
		if (check > 0)
		{
			hit = RayCast3D_hit(hit, data);
			return hit;
		}

		hit = RayCast3D_continue(data);
	}

	hit.isHit = false;
	return hit;
}*/
