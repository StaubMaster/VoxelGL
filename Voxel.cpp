
#include "Voxel.hpp"

Voxel::Voxel()
{
	ID = 0;
}
Voxel::Voxel(char id) :
	ID(id), Rotation(0)
{

}
Voxel::Voxel(char id, char rot) :
	ID(id), Rotation(rot)
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


