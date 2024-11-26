
#ifndef VOXELCHUNK_HPP
# define VOXELCHUNK_HPP
# include <iostream>

# include "../openGL/openGL.h"
# include "../openGL/Abstract/math3D.hpp"
# include "../openGL/Abstract/Point.hpp"

# include "Voxel.hpp"
# include "VoxelDataTable.hpp"
# include "VoxelRenderData.hpp"

# include "../AxisBox.hpp"
# include "../MemorySize.hpp"

//	!!!! when changing chunk size make sure to change it in the shader as well
# define Voxel_per_Side 16
# define Voxel_per_Chunk (Voxel_per_Side*Voxel_per_Side*Voxel_per_Side)
# define Vertex_per_Side (Voxel_per_Side+1)
# define Vertex_per_Chunk (Vertex_per_Side*Vertex_per_Side*Vertex_per_Side)

class VoxelChunk
{
	public:
		static void	Loop_Index(unsigned int & vox, int & ch);
		static void	Loop_Index(Undex3D & vox, Index3D & ch);
		static void	Voxel_Neighbour(char cardinal, Undex3D & vox, Index3D & ch);

	private:
		Voxel *			Data;
		const Index3D	Index;

		unsigned int	Buffer_Array;
		unsigned int	Buffer_Corner;
		unsigned int	Buffer_Index;
		unsigned int	Vertex_Count;

	public:
		VoxelChunk(Index3D idx);
		~VoxelChunk();
	private:
		VoxelChunk(const VoxelChunk & other);
		const VoxelChunk & operator =(const VoxelChunk & other);

	public:
		const Voxel & get(Undex3D idx) const;

	public:
		bool	isChunkIndex(Index3D idx) const;
		Index3D	getChunkIndex3D() const;
		Point	getChunkOffset() const;

		void	GenerateChunkLimit(VoxelDataTable & table, char axis_limit);
		void	GenerateFuzzyCenterCube(VoxelDataTable & table, int size2);
		void	GenerateVoxelRotationTest(VoxelDataTable & table);
		void	GeneratePlane(VoxelDataTable & table);

		int		CheckVoxel(Index3D idx);
		void	tryAdd(VoxelDataTable & table, Undex3D idx, char id, char orth);
		char	trySub(Undex3D idx);

		bool	IntersektBool(AxisBox & box);
		char	TouchVoxel(AxisBox & box, float size);

	public:
		void	UpdateBuffer(
					const VoxelChunk * Xn, const VoxelChunk * Xp,
					const VoxelChunk * Yn, const VoxelChunk * Yp,
					const VoxelChunk * Zn, const VoxelChunk * Zp);
		void	Draw(int Uni_Chunk_Pos) const;

		unsigned int	GeneralInfoMemData();
		unsigned int	GeneralInfoMemBuff();
};

#endif
