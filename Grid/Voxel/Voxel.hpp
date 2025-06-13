
#pragma once

# include <iostream>

# include "../../AxisBox.hpp"

# include "../../openGL/Abstract/Undex3D.hpp"
# include "../../openGL/Abstract/math3D.hpp"

# define VOXEL_NO_DRAW_BIT     0b001
# define VOXEL_NOT_SOLID_BIT   0b010
# define VOXEL_TRANSPARENT_BIT 0b100
# define VOXEL_AXIS_BITS 0b00111
# define VOXEL_SPIN_BITS 0b11000

struct	VoxelOrientation
{
	char	Data;

	VoxelOrientation(char axis, char spin);

	void	SetAxis(char axis);
	char	GetAxis() const;

	void	SetSpin(char spin);
	char	GetSpin() const;

	VoxelOrientation	ToNonRandom() const;
};

class	Voxel
{
	protected:
		char	ID;
		char	Category;
		VoxelOrientation	Orientation;

	public:
		Voxel();
		Voxel(char id);
		Voxel(char idx, char category, VoxelOrientation ori);
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
