
#ifndef VOXELCHUNK_HPP
# define VOXELCHUNK_HPP
# include "openGL/openGL.h"
# include "openGL/math3D.hpp"
# include <iostream>

class VoxelChunk
{
	const static unsigned int	Voxel_per_Side = 8;
	const static unsigned int	Voxel_per_Chunk = 8 * 8 * 8;
	const static unsigned int	Vertex_per_Side = 9;
	const static unsigned int	Vertex_per_Chunk = 9 * 9 * 9;

	static unsigned int XYZ_to_VoxelIndex(unsigned int x, unsigned int y, unsigned int z);
	static unsigned int XYZ_to_VertexIndex(unsigned int x, unsigned int y, unsigned int z);

	private:
		char *	Data;

		unsigned int	Buffer_Array;
		unsigned int	Buffer_Corner;
		unsigned int	Buffer_Index;
		unsigned int	Index_Count;

	public:
		VoxelChunk();
		~VoxelChunk();

	public:
		void	FillRandom();

	public:
		void	UpdateBufferVertex();
		void	UpdateBufferIndex();
		void	Draw();
};

#endif
