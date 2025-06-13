
#pragma once

# include <iostream>

# include "../../openGL/openGL.h"
# include "../../openGL/Abstract/math3D.hpp"
# include "../../openGL/Abstract/Point.hpp"

# include "../Voxel/Voxel.hpp"
# include "../Voxel/VoxelRenderData.hpp"
# include "../Template/VoxelDataTable.hpp"
# include "../Space/VoxelHover.hpp"
# include "../Template/Structure.hpp"

# include "../../AxisBox.hpp"
# include "../../MemorySize.hpp"

//	!!!! when changing chunk size make sure to change it in the shader as well
# define Voxel_per_Side 16
# define Voxel_per_Chunk (Voxel_per_Side*Voxel_per_Side*Voxel_per_Side)
# define Vertex_per_Side (Voxel_per_Side+1)
# define Vertex_per_Chunk (Vertex_per_Side*Vertex_per_Side*Vertex_per_Side)

/*
allocate
request Base
	generate Base
request Features (tree)
	give Requests to neighbouring chunks to generate
once Requests from self and all neighbours recieved
	generate Features
done
*/

/*
Feature Generation Request
simple
	: spheare {
		global box
	}
	: spheare {
		global location
		radius
	}

	Structure {
		Data of the Structure
	}
*/

class VoxelChunk
{
	public:
		static void	Loop_Index(unsigned int & vox, int & ch);
		static void	Loop_Index(Undex3D & vox, Index3D & ch);
		static void	Voxel_Neighbour(char cardinal, Undex3D & vox, Index3D & ch);

	private:
		struct RenderData
		{
			unsigned int	Buffer_Array;
			unsigned int	Buffer_Corner;
			unsigned int	Buffer_Index;
			unsigned int	Vertex_Count;

			bool							NeedsUpdate;
			bool							NeedsBind;
			VoxelRenderData::DataStream *	BufferStream;

			RenderData();
			~RenderData();
			RenderData(const RenderData & other) = delete;
			const RenderData & operator =(const RenderData & other) = delete;

			void	RequestUpdate();
			void	Update(const VoxelChunk * here,
						const VoxelChunk * Xn, const VoxelChunk * Xp,
						const VoxelChunk * Yn, const VoxelChunk * Yp,
						const VoxelChunk * Zn, const VoxelChunk * Zp);
			void	Bind();
			void	Draw() const;
		};

	public:
		RenderData		Render;

		bool			NeedsBase;
		bool			NeedsToRequest;
		bool			allRequestsGotten() const;
		bool			NeedsToGenRequest;

		bool			NeedsGeneration1;
		bool			NeedsGeneration2;

	private:
		Voxel *			Data;
		const Index3D	Index;

	public:
		VoxelChunk(Index3D idx);
		~VoxelChunk();
	private:
		VoxelChunk(const VoxelChunk & other);
		const VoxelChunk & operator =(const VoxelChunk & other);

	public:
		const Voxel & get(Undex3D idx) const;

		bool	isChunkIndex(Index3D idx) const;
		Index3D	getChunkIndex3D() const;
		Index3D	getChunkVoxelIndex3D() const;
		Point	getChunkOffset() const;

		int		CheckVoxel(Index3D idx);

		void	tryAdd(VoxelDataTable & table, VoxelHover hover, char id);
		char	trySub(VoxelHover hover);

		bool	IntersektBool(AxisBox & box);
		char	TouchVoxel(AxisBox & box, float size);

	public:
		void	RequestBufferUpdate();
		void	Draw(int Uni_Chunk_Pos) const;

		unsigned int	GeneralInfoMemData();
		unsigned int	GeneralInfoMemBuff();

	public:
		void	GenerateChunkLimit(VoxelDataTable & table, char axis_limit);
		void	GenerateFuzzyCenterCube(VoxelDataTable & table, int size2);
		void	GenerateVoxelRotationTest(VoxelDataTable & table);

		void	GeneratePlane(VoxelDataTable & table);

		void	GenerateTree(VoxelDataTable & table, Index3D tree_base);

		static void set(VoxelChunk * * chunks, Undex3D idx, Voxel vox);
		static void	GenerateFeature(VoxelDataTable & table, VoxelChunk * * chunks);
};
