
#ifndef VOXELHOVER_HPP
# define VOXELHOVER_HPP
# include "../openGL/Abstract/math3D.hpp"

struct VoxelHover
{
	bool			isValid;

	unsigned int	chunk_vector_idx;

	Index3D			chunk_idx;
	Undex3D			voxel_idx;

	RayCast3D_Hit	hit;
};

#endif
