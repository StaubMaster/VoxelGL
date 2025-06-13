
# pragma once

# include "../../openGL/openGL.h"
# include "../../openGL/Abstract/Undex3D.hpp"

# include "./Voxel.hpp"

# define TEXTURE_XM 0b00100
# define TEXTURE_XP 0b11000
# define TEXTURE_YM 0b01000
# define TEXTURE_YP 0b10100
# define TEXTURE_ZM 0b10000
# define TEXTURE_ZP 0b01100

# define TEXTURE_MIN_MIN 0b00
# define TEXTURE_MAX_MIN 0b10
# define TEXTURE_MIN_MAX 0b01
# define TEXTURE_MAX_MAX 0b11

class VoxelChunk;

struct VoxelRenderData
{
	public:
		struct TextureCoordFace
		{
			float	min_x;
			float	max_x;
			float	min_y;
			float	max_y;

			void	getCorner(float & x, float & y, bool Xbool, bool Ybool, bool swap) const;

			TextureCoordFace	FlipX() const;
			TextureCoordFace	FlipY() const;
			TextureCoordFace	Spin() const;
		};

	public:
		struct TextureCoordCube
		{
			TextureCoordFace	XM;	//	001
			TextureCoordFace	YM;	//	010
			TextureCoordFace	ZP;	//	011
			TextureCoordFace	ZM;	//	100
			TextureCoordFace	YP;	//	101
			TextureCoordFace	XP;	//	110
			bool TexSwap;

			TextureCoordFace	getFace(char idx, bool & texSwap) const;

			TextureCoordCube	SpinAroundX() const;
			TextureCoordCube	SpinAroundY() const;
			TextureCoordCube	SpinAroundZ() const;

			TextureCoordCube	RotateXM() const;
			TextureCoordCube	RotateXP() const;
			TextureCoordCube	RotateYM() const;
			TextureCoordCube	RotateYP() const;
			TextureCoordCube	RotateZM() const;
			TextureCoordCube	RotateZP() const;
		};

	private:
		struct Default
		{
			Default() = delete;

			static VoxelRenderData::TextureCoordCube Same;
			static VoxelRenderData::TextureCoordCube ZM;
			static VoxelRenderData::TextureCoordCube XM;
			static VoxelRenderData::TextureCoordCube YM;
			static VoxelRenderData::TextureCoordCube ZP;
			static VoxelRenderData::TextureCoordCube XP;
			static VoxelRenderData::TextureCoordCube YP;
		};

	//	======== ======== DATA ======== ========
	private:
		unsigned int	compressed_pos;

		//	this will also be compressed later
		unsigned int	tex_idx;
		float			tex_x;
		float			tex_y;

	public:
		VoxelRenderData();
	private:
		VoxelRenderData(Undex3D vox_idx, char tex_info, const Voxel & vox);

	public:
		struct DataStream
		{
			unsigned int		Length;
			VoxelRenderData *	Data;
			unsigned int		Index;

			DataStream(unsigned int len);
			~DataStream();

			void	Insert(VoxelRenderData vox);

			void	ToBuffer(unsigned int & count) const;

		private:
			void FaceN(Undex3D vox_idx, const Voxel & vox, char tex_axis, Undex3D udx[6]);
			void FaceP(Undex3D vox_idx, const Voxel & vox, char tex_axis, Undex3D udx[6]);

			void FaceXn(Undex3D vox_idx, const Voxel & vox);
			void FaceXp(Undex3D vox_idx, const Voxel & vox);
			void FaceYn(Undex3D vox_idx, const Voxel & vox);
			void FaceYp(Undex3D vox_idx, const Voxel & vox);
			void FaceZn(Undex3D vox_idx, const Voxel & vox);
			void FaceZp(Undex3D vox_idx, const Voxel & vox);

		public:
			void FaceX(Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p);
			void FaceY(Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p);
			void FaceZ(Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p);
		};
};
