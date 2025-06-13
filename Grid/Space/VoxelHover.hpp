
#pragma once

# include "../../openGL/Abstract/math3D.hpp"

struct VoxelHover
{
	bool			isValid;

	unsigned int	chunk_vector_idx;

	Index3D			chunk_idx;
	Undex3D			voxel_idx;

	RayCast3D_Hit	hit;
};
