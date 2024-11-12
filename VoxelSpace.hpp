
#ifndef VOXELSPACE_HPP
# define VOXELSPACE_HPP
# include "openGL/openGL.h"
# include "openGL/Abstract/math3D.hpp"
# include "VoxelChunk.hpp"
# include <iostream>
# include <vector>

class VoxelSpace
{
	public:
		struct Voxel_Hover
		{
			bool			isValid;
			unsigned int	chunk_idx;
			Undex3D			voxel_idx;
			char			cardinal;
		};

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

		char	tryAdd(Voxel_Hover hover);
		char	trySub(Voxel_Hover hover);

		void	Draw(int Uni_Chunk_Pos) const;
		void	DrawBound() const;
		void	DrawHover(Voxel_Hover hover) const;

		Voxel_Hover		Cross(Point pos, Point dir);
};

#endif
