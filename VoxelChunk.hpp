
#ifndef VOXELCHUNK_HPP
# define VOXELCHUNK_HPP
# include "openGL/openGL.h"
# include "openGL/Abstract/math3D.hpp"
# include "openGL/Abstract/Point.hpp"
# include "Voxel.hpp"
# include "Box.hpp"
# include "MemorySize.hpp"
# include <iostream>

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
		unsigned int	Index_Count;
		unsigned int	Vertex_Count;

	public:
		VoxelChunk(Index3D idx);
		~VoxelChunk();
	private:
		VoxelChunk(const VoxelChunk & other);
		const VoxelChunk & operator =(const VoxelChunk & other);
		const Voxel & get(Undex3D idx) const;

	public:
		bool	isChunkIndex(Index3D idx) const;
		Index3D	getChunkIndex3D() const;
		Point	getChunkOffset() const;

		void	GenerateChunkLimit(char axis_limit);
		void	GenerateFuzzyCenterCube(int size2);

		int		CheckVoxel(Index3D idx);
		char	tryReplace(Undex3D idx, char d);

	private:
		void	UpdateBufferVertex();
		void	UpdateBufferIndex(
					const VoxelChunk * Xn, const VoxelChunk * Xp,
					const VoxelChunk * Yn, const VoxelChunk * Yp,
					const VoxelChunk * Zn, const VoxelChunk * Zp);
	public:
		void	UpdateBuffer(
					const VoxelChunk * Xn, const VoxelChunk * Xp,
					const VoxelChunk * Yn, const VoxelChunk * Yp,
					const VoxelChunk * Zn, const VoxelChunk * Zp);
		void	Draw(int Uni_Chunk_Pos) const;



	public:
		struct VoxelDrawData
		{
			private:
				unsigned int	compressed_pos;

				//	this will also be compressed later
				unsigned int	tex_idx;
				float			tex_x;
				float			tex_y;

			public:
				static VoxelDrawData compress(Undex3D vox_idx, int tex_idx, char corn);
		};
	private:
		static void FaceXn(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);
		static void FaceXp(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);
		static void FaceYn(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);
		static void FaceYp(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);
		static void FaceZn(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);
		static void FaceZp(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);

		static void FaceX(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p);
		static void FaceY(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p);
		static void FaceZ(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p);

		static void FaceX(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p);
		static void FaceY(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p);
		static void FaceZ(VoxelDrawData * data, unsigned int & idx, Undex3D vox_idx, const VoxelChunk * here, const VoxelChunk * ch_n, const VoxelChunk * ch_p);



	private:
		static void IndexFaceXn(unsigned int * index, unsigned int & idx, Undex3D vox);
		static void IndexFaceXp(unsigned int * index, unsigned int & idx, Undex3D vox);
		static void IndexFaceYn(unsigned int * index, unsigned int & idx, Undex3D vox);
		static void IndexFaceYp(unsigned int * index, unsigned int & idx, Undex3D vox);
		static void IndexFaceZn(unsigned int * index, unsigned int & idx, Undex3D vox);
		static void IndexFaceZp(unsigned int * index, unsigned int & idx, Undex3D vox);

		static void IndexFaceX(unsigned int * index, unsigned int & idx, Undex3D vox, const Voxel * vn, const Voxel * vp);
		static void IndexFaceY(unsigned int * index, unsigned int & idx, Undex3D vox, const Voxel * vn, const Voxel * vp);
		static void IndexFaceZ(unsigned int * index, unsigned int & idx, Undex3D vox, const Voxel * vn, const Voxel * vp);

		static void IndexFaceX(unsigned int * index, unsigned int & idx, Undex3D vox, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p);
		static void IndexFaceY(unsigned int * index, unsigned int & idx, Undex3D vox, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p);
		static void IndexFaceZ(unsigned int * index, unsigned int & idx, Undex3D vox, const VoxelChunk * t, const VoxelChunk * n, const VoxelChunk * p);
};

#endif
