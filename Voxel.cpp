
#include "Voxel.hpp"

Voxel::Voxel() :
	ID(0), Axis(0), Spin(0)
{

}
Voxel::Voxel(char id) :
	ID(id), Axis(0), Spin(0)
{

}
Voxel::Voxel(char id, char axis, char spin) :
	ID(id), Axis(axis), Spin(spin)
{

}
Voxel::~Voxel()
{
	
}



bool	Voxel::isSolid() const
{
	if (ID == 0)
	{
		return (false);
	}
	return (true);
}
char	Voxel::getAxis() const
{
	return (Axis);
}
char	Voxel::getSpin() const
{
	return (Spin);
}



/*	IDEA

Aligned : voxels will allways face the same way

UnAligned : rotation is random

AxisAligned : specify and Axis in which to face

*/

Voxel	Voxel::Aligned(char id)
{
	return Voxel(id);
}
Voxel	Voxel::UnAligned(char id)
{
	return Voxel(id);
}
Voxel	Voxel::AxisAligned(char id, char axis, char spin)
{
	if (axis == 1 || axis == 2)
		axis = 1;
	else if (axis == 3 || axis == 4)
		axis = 0;
	else if (axis == 5 || axis == 6)
		axis = 2;
	return Voxel(id, axis, spin);
}
