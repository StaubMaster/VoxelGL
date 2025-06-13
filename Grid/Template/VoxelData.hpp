
#pragma once

# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>

# include "../Voxel/Voxel.hpp"
# include "../Space/VoxelHover.hpp"

# include "../../openGL/openGL.h"
# include "../../FileParse/PNG/PNG_Image.hpp"

struct VoxelData
{
	const char *	fileName;
	bool			isNoDraw;
	bool			isNotSolid;
	bool			isTransparent;
	bool			isFixedAxis;
	bool			isFixedSpin;

	VoxelData(const char * fileName,
		bool isNoDraw,
		bool isNotSolid,
		bool isTransparent,
		bool isFixedAxis,
		bool isFixedSpin
	);

	Voxel	ToVoxel(char idx, char ori) const;
	Voxel	ToVoxelForce(char idx, char ori) const;
	Voxel	ToVoxel(char idx, VoxelHover hover) const;
};
