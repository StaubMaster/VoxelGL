
#include "Index3D.hpp"

Index3D::Index3D() : x(0), y(0), z(0)
{

}
Index3D::Index3D(int x, int y, int z) : x(x), y(y), z(z)
{

}
Index3D::~Index3D()
{

}
Index3D::Index3D(const Index3D & other) : x(other.x), y(other.y), z(other.z)
{

}
const Index3D & Index3D::operator =(const Index3D & other)
{
	this -> x = other.x;
	this -> y = other.y;
	this -> z = other.z;
	return (*this);
}

Index3D Index3D::operator +(const Index3D & other) const
{
	return Index3D(
		x + other.x,
		y + other.y,
		z + other.z
	);
}
Index3D Index3D::operator -(const Index3D & other) const
{
	return Index3D(
		x - other.x,
		y - other.y,
		z - other.z
	);
}



Index3D Index3D::Xn() const
{
	return Index3D(x - 1, y, z);
}
Index3D Index3D::Xp() const
{
	return Index3D(x + 1, y, z);
}
Index3D Index3D::Yn() const
{
	return Index3D(x, y - 1, z);
}
Index3D Index3D::Yp() const
{
	return Index3D(x, y + 1, z);
}
Index3D Index3D::Zn() const
{
	return Index3D(x, y, z - 1);
}
Index3D Index3D::Zp() const
{
	return Index3D(x, y, z + 1);
}



bool	Index3D::Box_inclusive(Index3D idx, Index3D min, Index3D max)
{
	return	(idx.x >= min.x && idx.x <= max.x) &&
			(idx.y >= min.y && idx.y <= max.y) &&
			(idx.z >= min.z && idx.z <= max.z);
}
bool	Index3D::Box_exclusive(Index3D idx, Index3D min, Index3D max)
{
	return	(idx.x > min.x && idx.x < max.x) &&
			(idx.y > min.y && idx.y < max.y) &&
			(idx.z > min.z && idx.z < max.z);
}
