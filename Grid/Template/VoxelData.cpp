#include "VoxelData.hpp"



VoxelData::VoxelData(const char * fileName,
	bool isNoDraw,
	bool isNotSolid,
	bool isTransparent,
	bool isFixedAxis,
	bool isFixedSpin
) :
	fileName(fileName),
	isNoDraw(isNoDraw),
	isNotSolid(isNotSolid),
	isTransparent(isTransparent),
	isFixedAxis(isFixedAxis),
	isFixedSpin(isFixedSpin)
{

}

Voxel	VoxelData::ToVoxel(char idx, char ori) const
{
	char category = 0;
	if (isNoDraw)      { category |= VOXEL_NO_DRAW_BIT; }
	if (isNotSolid)    { category |= VOXEL_NOT_SOLID_BIT; }
	if (isTransparent) { category |= VOXEL_TRANSPARENT_BIT; }

	char axis;
	if (isFixedAxis) { axis = ori & VOXEL_AXIS_BITS; } else { axis = (std::rand() % 6) + 1; }
	char spin;
	if (isFixedSpin) { spin = ori & VOXEL_SPIN_BITS; } else { spin = (std::rand() % 4) << 3; }

	//return Voxel(idx, category, axis | spin);
	return Voxel(idx, category, VoxelOrientation(axis, spin));
}
Voxel	VoxelData::ToVoxelForce(char idx, char ori) const
{
	char category = 0;
	if (isNoDraw)      { category |= VOXEL_NO_DRAW_BIT; }
	if (isNotSolid)    { category |= VOXEL_NOT_SOLID_BIT; }
	if (isTransparent) { category |= VOXEL_TRANSPARENT_BIT; }

	char axis;
	axis = ori & VOXEL_AXIS_BITS;
	char spin;
	spin = ori & VOXEL_SPIN_BITS;

	//return Voxel(idx, category, axis | spin);
	return Voxel(idx, category, VoxelOrientation(axis, spin));
}
Voxel	VoxelData::ToVoxel(char idx, VoxelHover hover) const
{
	char category = 0;
	if (isNoDraw)      { category |= VOXEL_NO_DRAW_BIT; }
	if (isNotSolid)    { category |= VOXEL_NOT_SOLID_BIT; }
	if (isTransparent) { category |= VOXEL_TRANSPARENT_BIT; }

	char axis;
	if (isFixedAxis) { axis = hover.hit.from_axis; } else { axis = (std::rand() % 6) + 1; }
	char spin;
	//if (isFixedSpin) { spin = (hover.hit.dir2 << 3) & VOXEL_SPIN_BITS; } else { spin = (std::rand() % 4) << 3; }
	spin = 0;

	//return Voxel(idx, category, axis | spin);
	return Voxel(idx, category, VoxelOrientation(axis, spin));
}
