
#ifndef VOXEL_HPP
# define VOXEL_HPP
# include <iostream>
# include "openGL/Abstract/Undex3D.hpp"

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

class Voxel
{
	private:
		char	ID;
	
	public:
		Voxel();
		Voxel(char id);

		bool	isSolid() const;


	public:
		struct RenderData
		{
			private:
				unsigned int	compressed_pos;

				//	this will also be compressed later
				unsigned int	tex_idx;
				float			tex_x;
				float			tex_y;

			public:
				static RenderData compress(Undex3D vox_idx, int tex_idx, char tex_info);
		};

	public:
		static void FaceXn(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);
		static void FaceXp(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);
		static void FaceYn(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);
		static void FaceYp(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);
		static void FaceZn(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);
		static void FaceZp(RenderData * data, unsigned int & idx, Undex3D vox_idx, int tex_idx);

		static void FaceX(RenderData * data, unsigned int & idx, Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p);
		static void FaceY(RenderData * data, unsigned int & idx, Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p);
		static void FaceZ(RenderData * data, unsigned int & idx, Undex3D vox_idx, const Voxel * v_n, const Voxel * v_p);
};

#endif
