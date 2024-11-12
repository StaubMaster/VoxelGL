
#ifndef VOXELSPACE_HPP
# define VOXELSPACE_HPP
# include "openGL/openGL.h"
# include "openGL/Abstract/math3D.hpp"
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

		void	FillRandom();
		void	UpdateBuffer(int x, int y, int z);

		VoxelChunk *	FindChunkPtr(int x, int y, int z);
		VoxelChunk *	FindChunkPtr(Index3D idx);
		unsigned int	FindChunkIdx(Index3D idx);
		int				CheckChunk(Index3D idx);

		char	trySub(unsigned int ch, Undex3D vox);

		void	Draw(int Uni_Chunk_Pos) const;
		void	DrawBound() const;

		Undex3D		Cross(Point pos, Point dir, unsigned int & chunk_idx);
};

#endif
