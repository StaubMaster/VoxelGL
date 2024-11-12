
#include "Voxel.hpp"

Voxel::Voxel()
{
	ID = 0;
}
Voxel::Voxel(char id) :
	ID(id)
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
