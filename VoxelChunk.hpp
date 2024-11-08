
#ifndef VOXELCHUNK_HPP
# define VOXELCHUNK_HPP
# include "openGL/openGL.h"
# include "openGL/math3D.hpp"
# include <iostream>

class VoxelChunk
{
	const static unsigned int	Side_Len = 8;
	const static unsigned int	Data_Size = 512;

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
		void	UpdateBufferCorner();
		void	UpdateBufferIndex();
		void	Draw();
};

#endif
