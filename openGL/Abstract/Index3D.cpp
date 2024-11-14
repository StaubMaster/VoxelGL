
#include "Index3D.hpp"

Index3D::Index3D() : x(0), y(0), z(0)
{

}
Index3D::Index3D(int i) : x(i), y(i), z(i)
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



int	Index3D::ToIndex(int size_per_side) const
{
	return (
		x + 
		y * size_per_side +
		z * size_per_side * size_per_side
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



bool Index3D::loop_inclusive(Index3D & idx, Index3D min, Index3D max)
{
	idx.z++;
	if (idx.z > max.z)
	{
		idx.z = min.z,
		idx.y++;
		if (idx.y > max.y)
		{
			idx.y = min.y;
			idx.x++;
			if (idx.x > max.x)
			{
				idx.x = min.x;
				return (false);
			}
		}
	}
	return (true);
}
bool Index3D::loop_exclusive(Index3D & idx, Index3D min, Index3D max)
{
	idx.z++;
	if (idx.z >= max.z)
	{
		idx.z = min.z,
		idx.y++;
		if (idx.y >= max.y)
		{
			idx.y = min.y;
			idx.x++;
			if (idx.x >= max.x)
			{
				idx.x = min.x;
				return (false);
			}
		}
	}
	return (true);
}
bool Index3D::loop_inclusive(Index3D & idx, int min, int max)
{
	idx.z++;
	if (idx.z > max)
	{
		idx.z = min,
		idx.y++;
		if (idx.y > max)
		{
			idx.y = min;
			idx.x++;
			if (idx.x > max)
			{
				idx.x = min;
				return (false);
			}
		}
	}
	return (true);
}
bool Index3D::loop_exclusive(Index3D & idx, int min, int max)
{
	idx.z++;
	if (idx.z >= max)
	{
		idx.z = min,
		idx.y++;
		if (idx.y >= max)
		{
			idx.y = min;
			idx.x++;
			if (idx.x >= max)
			{
				idx.x = min;
				return (false);
			}
		}
	}
	return (true);
}



std::ostream & operator <<(std::ostream & o, const Index3D & idx)
{
	o << idx.x << ":" << idx.y << ":" << idx.z;
	return o;
}
