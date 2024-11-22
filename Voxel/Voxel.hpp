
#ifndef VOXEL_HPP
# define VOXEL_HPP
# include <iostream>

# include "../openGL/Abstract/Undex3D.hpp"

# define VOXEL_AXIS_XM 0b000
# define VOXEL_AXIS_XP 0b000
# define VOXEL_AXIS_YM 0b000
# define VOXEL_AXIS_YP 0b000
# define VOXEL_AXIS_ZM 0b000
# define VOXEL_AXIS_ZP 0b000

class Voxel
{
	protected:
		char	ID;
		char	Axis;
		char	Spin;

	private:
	public:
		Voxel();
		Voxel(char id);
		Voxel(char id, char axis, char spin);
		~Voxel();

	public:
		bool	isSolid() const;
		char	getID() const;
		char	getAxis() const;
		char	getSpin() const;

		static	Voxel	Aligned(char id);
		static	Voxel	UnAligned(char id);
		static	Voxel	AxisAligned(char id, char axis, char spin);
};

#endif
