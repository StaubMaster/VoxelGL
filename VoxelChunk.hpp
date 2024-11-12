
#ifndef VOXELCHUNK_HPP
# define VOXELCHUNK_HPP
# include "openGL/openGL.h"
# include "openGL/Abstract/math3D.hpp"
# include "openGL/Abstract/Point.hpp"
# include "Box.hpp"
# include "MemorySize.hpp"
# include <iostream>

class VoxelChunk
{
	public:
		const static unsigned int	Voxel_per_Side = 8;
		const static unsigned int	Voxel_per_Chunk = 8 * 8 * 8;
		const static unsigned int	Vertex_per_Side = 9;
		const static unsigned int	Vertex_per_Chunk = 9 * 9 * 9;

		static unsigned int XYZ_to_VoxelIndex(unsigned int x, unsigned int y, unsigned int z);
		static unsigned int XYZ_to_VertexIndex(unsigned int x, unsigned int y, unsigned int z);
		static unsigned int XYZ_to_VoxelIndex(Undex3D idx);

		static void IndexFaceXn(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z);
		static void IndexFaceXp(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z);
		static void IndexFaceYn(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z);
		static void IndexFaceYp(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z);
		static void IndexFaceZn(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z);
		static void IndexFaceZp(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z);

	private:
		char *		Data;
		const int	Chunk_X;
		const int	Chunk_Y;
		const int	Chunk_Z;

		unsigned int	Buffer_Array;
		unsigned int	Buffer_Corner;
		unsigned int	Buffer_Index;
		unsigned int	Index_Count;

	public:
		VoxelChunk(int x, int y, int z);
		~VoxelChunk();
		VoxelChunk(const VoxelChunk & other);
	private:
		const VoxelChunk & operator =(const VoxelChunk & other);

	public:
		bool	isChunkIndex(int x, int y, int z) const;
		bool	isChunkIndex(Index3D idx) const;

		void	getChunkIndex(int & x, int & y, int & z) const;
		Point	getChunkOffset() const;

		void	FillRandom();
		int		CheckVoxel(Index3D idx);

		char	trySub(Undex3D idx);

	public:
		void	UpdateBufferVertex();
		void	UpdateBufferIndex(
					const VoxelChunk * Xn, const VoxelChunk * Xp,
					const VoxelChunk * Yn, const VoxelChunk * Yp,
					const VoxelChunk * Zn, const VoxelChunk * Zp);
		void	Draw(int Uni_Chunk_Pos) const;

		struct ChunkIndex
		{
			unsigned int x;
			unsigned int y;
			unsigned int z;
		};

		static Box	getVoxelBox(unsigned int x, unsigned int y, unsigned int z, Point off);
		static Box	getChunkBox(Index3D);
};

#endif
