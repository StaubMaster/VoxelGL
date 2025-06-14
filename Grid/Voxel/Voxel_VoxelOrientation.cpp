#include "Voxel.hpp"



VoxelOrientation::VoxelOrientation(char axis, char spin)
{
	Data = 0;
	SetAxis(axis);
	SetSpin(spin);
}
void	VoxelOrientation::SetAxis(char axis)
{
	/*if (axis == AXIS_BITS_RAND)
	{
		Data = (Data & 0b11111000) | ((std::rand() % 6) + 1);
	}
	else
	{
		Data = (Data & 0b11111000) | (axis);
	}*/
	Data = (Data & 0b11111000) | (axis);
}
char	VoxelOrientation::GetAxis() const
{
	return (Data & 0b00000111);
}
void	VoxelOrientation::SetSpin(char spin)
{
	(void)spin;
	/*if (spin == 0b100)
	{
		Data = (Data & 0b11100111) | ((std::rand() % 4) << 3);
	}
	else
	{
		char axis = GetAxis();
		if (axis == AXIS_BITS_XN)
		{
			if (spin == AXIS_BITS_YN) { spin = 0; }
			else if (spin == AXIS_BITS_YN) { spin = 1; }
			else if (spin == AXIS_BITS_YN) { spin = 2; }
			else if (spin == AXIS_BITS_YN) { spin = 3; }
		}
		Data = (Data & 0b11100111) | (spin << 3);
	}*/
	Data = (Data & 0b11100111) | ((std::rand() % 4) << 3);
}
char	VoxelOrientation::GetSpin() const
{
	return ((Data & 0b00011000) >> 3);
}
VoxelOrientation	VoxelOrientation::ToNonRandom() const
{
	char	axis = GetAxis();
	char	spin = GetSpin();

	if (axis == AXIS_BITS_RAND)
	{
		axis = (std::rand() % 6) + 1;
	}

	{
		spin = (std::rand() % 4) << 3;
	}

	return VoxelOrientation(axis, spin);
}

