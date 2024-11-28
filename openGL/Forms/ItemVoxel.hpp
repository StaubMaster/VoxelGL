
#ifndef ITEMVOXEL_HPP
# define ITEMVOXEL_HPP
# include "../openGL.h"
# include "../Shader.hpp"
# include "../Abstract/Angle.hpp"

class ItemVoxel
{
	public:
		static void	Create();
		static void	Delete();

		static void	Update(float time);

		static void	Draw(float x, float y, int idx);
};

#endif
