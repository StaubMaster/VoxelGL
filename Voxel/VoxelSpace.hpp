
#ifndef VOXELSPACE_HPP
# define VOXELSPACE_HPP
# include <iostream>
# include <vector>

# include "../openGL/openGL.h"
# include "../openGL/Abstract/math3D.hpp"

# include "VoxelChunk.hpp"
# include "VoxelHover.hpp"

class VoxelSpace
{
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

		char	tryAdd(VoxelHover hover, char id);
		char	trySub(VoxelHover hover, char id);

		bool	IntersektBool(AxisBox & box);
		char	TouchVoxel(AxisBox & box, float size);

		void	Draw(int Uni_Chunk_Pos) const;
		void	DrawBound() const;
		void	DrawHover(VoxelHover hover) const;

		unsigned int	GeneralInfoChunksCount();
		unsigned int	GeneralInfoMemSumChunksData();
		unsigned int	GeneralInfoMemSumChunksBuff();

		VoxelHover		Cross(Point pos, Point dir);
};

#endif
