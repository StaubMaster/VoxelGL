
#include "Voxel.hpp"
#include "../openGL/Abstract/math3D.hpp"

Voxel::Voxel() :
	ID(0),
	Category(VOXEL_NO_DRAW_BIT | VOXEL_NOT_SOLID_BIT),
	Orientation(0)
{

}
Voxel::Voxel(char id) :
	ID(id),
	Category(VOXEL_NO_DRAW_BIT | VOXEL_NOT_SOLID_BIT),
	Orientation(0)
{

}
Voxel::Voxel(char id, char category, char orientation) :
	ID(id),
	Category(category),
	Orientation(orientation)
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
	return (Orientation & VOXEL_AXIS_BITS);
}
char	Voxel::getSpin() const
{
	return (Orientation & VOXEL_SPIN_BITS) >> 3;
}



char	Voxel::Orth_To_Axis(char orth)
{
	if (orth == CARDINAL_X_NEGATIVE)
		return (0b001);
	else if (orth == CARDINAL_X_POSITIVE)
		return (0b110);
	else if (orth == CARDINAL_Y_NEGATIVE)
		return (0b010);
	else if (orth == CARDINAL_Y_POSITIVE)
		return (0b101);
	else if (orth == CARDINAL_Z_NEGATIVE)
		return (0b100);
	else if (orth == CARDINAL_Z_POSITIVE)
		return (0b011);
	return (0);
}
