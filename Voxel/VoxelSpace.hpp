
#ifndef VOXELSPACE_HPP
# define VOXELSPACE_HPP
# include <iostream>
# include <vector>

# include "../openGL/openGL.h"
# include "../openGL/Abstract/math3D.hpp"

# include "VoxelChunk.hpp"

class VoxelSpace
{
	public:
		struct Voxel_Hover
		{
			bool			isValid;
			unsigned int	chunk_vec_idx;
			Index3D			chunk_idx;
			Undex3D			voxel_idx;
			char			cardinal;
			Point			dir;
		};

	private:
		std::vector<VoxelChunk * > Chunks;
		VoxelDataTable & Table;

	public:
		VoxelSpace(VoxelDataTable & table);
		~VoxelSpace();

		VoxelChunk *	FindChunkPtr(Index3D idx);
		unsigned int	FindChunkIdx(Index3D idx);
		int				CheckChunk(Index3D idx);

		void	FillRandom();
		void	AddChunk(Index3D idx);
		void	SubChunk(Index3D idx);
		void	AddChunksRange(Index3D idx, int range);
		void	SubChunksRange(Index3D idx, int range);

		void	UpdateBuffer(Index3D idx);
		void	UpdateBufferNeighbours(Index3D idx);

		char	tryAdd(Voxel_Hover hover, char id);
		char	trySub(Voxel_Hover hover, char id);

		Point	CheckBoxCollision(Box & box);

		void	Draw(int Uni_Chunk_Pos) const;
		void	DrawBound() const;
		void	DrawHover(Voxel_Hover hover) const;

		Voxel_Hover		Cross(Point pos, Point dir);
};

#endif
