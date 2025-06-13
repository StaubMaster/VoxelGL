#include "Voxel.hpp"



Voxel::Voxel() :
	ID(0),
	Category(VOXEL_NO_DRAW_BIT | VOXEL_NOT_SOLID_BIT),
	Orientation(0, 0)
{

}
Voxel::Voxel(char id) :
	ID(id),
	Category(VOXEL_NO_DRAW_BIT | VOXEL_NOT_SOLID_BIT),
	Orientation(0, 0)
{

}
Voxel::Voxel(char id, char category, VoxelOrientation orientation) :
	ID(id),
	Category(category),
	Orientation(orientation.ToNonRandom())
{

}
Voxel::~Voxel()
{

}


Voxel::Voxel(const Voxel & other) :
	ID(other.ID),
	Category(other.Category),
	Orientation(other.Orientation)
{

}
const Voxel & Voxel::operator =(const Voxel & other)
{
	this -> ID = other.ID;
	this -> Category = other.Category;
	this -> Orientation = other.Orientation;
	return *this;
}





char	Voxel::getID() const
{
	return (ID);
}
bool	Voxel::isDraw() const
{
	return !(Category & VOXEL_NO_DRAW_BIT);
}
bool	Voxel::isSolid() const
{
	return !(Category & VOXEL_NOT_SOLID_BIT);
}
bool	Voxel::isTransparent() const
{
	return (Category & VOXEL_TRANSPARENT_BIT);
}
char	Voxel::getAxis() const
{
	//return (Orientation & VOXEL_AXIS_BITS);
	return Orientation.GetAxis();
}
char	Voxel::getSpin() const
{
	//return (Orientation & VOXEL_SPIN_BITS) >> 3;
	return Orientation.GetSpin();
}
