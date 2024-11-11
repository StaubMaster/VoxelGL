
#ifndef VOXELCHUNK_HPP
# define VOXELCHUNK_HPP
# include "openGL/openGL.h"
# include "openGL/math3D.hpp"
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
		void	getChunkIndex(int & x, int & y, int & z) const;
		Point	getChunkOffset() const;
		void	FillRandom();

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

		ChunkIndex	Cross(Point pos, Point dir);
		static int	CheckVoxel(const void * obj, Index3D idx);

		static Box	getVoxelBox(unsigned int x, unsigned int y, unsigned int z, Point off);
		static Box	getChunkBox(Index3D);
};

#endif
