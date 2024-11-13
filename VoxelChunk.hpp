
#ifndef VOXELCHUNK_HPP
# define VOXELCHUNK_HPP
# include "openGL/openGL.h"
# include "openGL/Abstract/math3D.hpp"
# include "openGL/Abstract/Point.hpp"
# include "Voxel.hpp"
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

		static void	Loop_Index(unsigned int & vox, int & ch);
		static void	Loop_Index(Undex3D & vox, Index3D & ch);
		static void	Voxel_Neighbour(char cardinal, Undex3D & vox, Index3D & ch);

	private:
		static void IndexFaceXn(unsigned int * index, unsigned int idx, Undex3D vox);
		static void IndexFaceXp(unsigned int * index, unsigned int idx, Undex3D vox);
		static void IndexFaceYn(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z);
		static void IndexFaceYp(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z);
		static void IndexFaceZn(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z);
		static void IndexFaceZp(unsigned int * index, unsigned int idx, unsigned int x, unsigned int y, unsigned int z);

		static void IndexFaceX(unsigned int * index, unsigned int & idx, Undex3D vox, const Voxel * vn, const Voxel * vp);
		static void IndexFaceY(unsigned int * index, unsigned int & idx, unsigned int x, unsigned int y, unsigned int z, const Voxel * vn, const Voxel * vp);
		static void IndexFaceZ(unsigned int * index, unsigned int & idx, unsigned int x, unsigned int y, unsigned int z, const Voxel * vn, const Voxel * vp);

		static void IndexFaceX(unsigned int * index, unsigned int & idx, Undex3D vox, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p);
		static void IndexFaceY(unsigned int * index, unsigned int & idx, unsigned int x, unsigned int y, unsigned int z, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p);
		static void IndexFaceZ(unsigned int * index, unsigned int & idx, unsigned int x, unsigned int y, unsigned int z, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p);

	private:
		Voxel *			Data;
		const Index3D	Index;

		unsigned int	Buffer_Array;
		unsigned int	Buffer_Corner;
		unsigned int	Buffer_Index;
		unsigned int	Index_Count;

	public:
		VoxelChunk(Index3D idx);
		~VoxelChunk();
	private:
		VoxelChunk(const VoxelChunk & other);
		const VoxelChunk & operator =(const VoxelChunk & other);
		const Voxel & get(unsigned int x, unsigned int y, unsigned int z) const;
		const Voxel & get(Undex3D idx) const;

	public:
		bool	isChunkIndex(Index3D idx) const;
		Index3D	getChunkIndex3D() const;
		Point	getChunkOffset() const;

		void	FillRandom();
		int		CheckVoxel(Index3D idx);

		char	tryReplace(Undex3D idx, char d);

	public:
		void	UpdateBufferVertex();
		void	UpdateBufferIndex(
					const VoxelChunk * Xn, const VoxelChunk * Xp,
					const VoxelChunk * Yn, const VoxelChunk * Yp,
					const VoxelChunk * Zn, const VoxelChunk * Zp);
		void	Draw(int Uni_Chunk_Pos) const;

		static Box	getVoxelBox(unsigned int x, unsigned int y, unsigned int z, Point off);
		static Box	getChunkBox(Index3D idx);
};

#endif
