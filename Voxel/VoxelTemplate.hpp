
#pragma once

# include "Voxel.hpp"

struct VoxelTemplate
{
	const char *	FileName;
	int				ID;

	bool	IsNoDraw;
	bool	IsNotSolid;
	bool	IsTransparent;

/*
	Orientation Category
	axis					|	spin
	------------------------|-----------------------
	random					|	random
	hover face				|	random
	hover face				|	hover dir
*/
	bool	IsFixedAxis;
	bool	IsFixedSpin;

	VoxelTemplate(const char * fileName,
		bool isNoDraw,
		bool isNotSolid,
		bool isTransparent,
		bool isFixedAxis,
		bool isFixedSpin
	);

	Voxel	ToVoxelBase(char ori);
	Voxel	ToVoxelForce(char ori);
};
