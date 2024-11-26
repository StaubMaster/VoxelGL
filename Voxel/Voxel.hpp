
#ifndef VOXEL_HPP
# define VOXEL_HPP
# include <iostream>

# include "../AxisBox.hpp"

# include "../openGL/Abstract/Undex3D.hpp"

# define VOXEL_NO_DRAW_BIT     0b001
# define VOXEL_NOT_SOLID_BIT   0b010
# define VOXEL_TRANSPARENT_BIT 0b100
# define VOXEL_AXIS_BITS 0b00111
# define VOXEL_SPIN_BITS 0b11000

class Voxel
{
	protected:
		char	ID;

		char	Category;
		char	Orientation;

	public:
		Voxel();
		Voxel(char id);
		Voxel(char idx, char category, char orientation);
		~Voxel();

		Voxel(const Voxel & other);
		const Voxel & operator =(const Voxel & other);

	public:
		char	getID() const;

		bool	isDraw() const;
		bool	isSolid() const;
		bool	isTransparent() const;

		char	getAxis() const;
		char	getSpin() const;
};

#endif
