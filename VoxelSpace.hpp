
#ifndef VOXELSPACE_HPP
# define VOXELSPACE_HPP
# include "openGL/openGL.h"
# include "openGL/math3D.hpp"
# include "VoxelChunk.hpp"
# include <iostream>
# include <vector>

# define CHUNK_NOT_FOUND_IDX 0xFFFFFFFFFFFFFFFF

class VoxelSpace
{
	private:
		std::vector<VoxelChunk> Chunks;

	public:
		VoxelSpace();
		~VoxelSpace();

		VoxelChunk *	FindChunkPtr(int x, int y, int z);

		void	Draw(int Uni_Chunk_Pos) const;
};

#endif
