
#ifndef VOXEL_HPP
# define VOXEL_HPP
# include <iostream>
# include "openGL/Abstract/Undex3D.hpp"

class Voxel
{
	private:
	public:
		char	ID;
		char	Rotation;

	public:
		Voxel();
		Voxel(char id);
		Voxel(char id, char rot);

		bool	isSolid() const;
};

#endif
