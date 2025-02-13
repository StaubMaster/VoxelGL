
#include "Undex3D.hpp"

Undex3D::Undex3D() : x(0), y(0), z(0)
{

}
Undex3D::Undex3D(unsigned int x, unsigned int y, unsigned int z) : x(x), y(y), z(z)
{

}
Undex3D::~Undex3D()
{

}
Undex3D::Undex3D(const Undex3D & other) : x(other.x), y(other.y), z(other.z)
{

}
const Undex3D & Undex3D::operator =(const Undex3D & other)
{
	this -> x = other.x;
	this -> y = other.y;
	this -> z = other.z;
	return (*this);
}



Undex3D Undex3D::operator +(const Undex3D & other) const
{
	return Undex3D(
		x + other.x,
		y + other.y,
		z + other.z
	);
}
Undex3D Undex3D::operator -(const Undex3D & other) const
{
	return Undex3D(
		x - other.x,
		y - other.y,
		z - other.z
	);
}



unsigned int	Undex3D::ToIndex(unsigned int size_per_side) const
{
	return (
		x + 
		y * size_per_side +
		z * size_per_side * size_per_side
	);
}



Undex3D Undex3D::Xn() const
{
	return Undex3D(x - 1, y, z);
}
Undex3D Undex3D::Xp() const
{
	return Undex3D(x + 1, y, z);
}
Undex3D Undex3D::Yn() const
{
	return Undex3D(x, y - 1, z);
}
Undex3D Undex3D::Yp() const
{
	return Undex3D(x, y + 1, z);
}
Undex3D Undex3D::Zn() const
{
	return Undex3D(x, y, z - 1);
}
Undex3D Undex3D::Zp() const
{
	return Undex3D(x, y, z + 1);
}



Undex3D	Undex3D::set_get_X(unsigned int new_x) const
{
	return Undex3D(new_x, y, z);
}
Undex3D	Undex3D::set_get_Y(unsigned int new_y) const
{
	return Undex3D(x, new_y, z);
}
Undex3D	Undex3D::set_get_Z(unsigned int new_z) const
{
	return Undex3D(x, y, new_z);
}



bool	Undex3D::Box_inclusive(Undex3D idx, Undex3D min, Undex3D max)
{
	return	(idx.x >= min.x && idx.x <= max.x) &&
			(idx.y >= min.y && idx.y <= max.y) &&
			(idx.z >= min.z && idx.z <= max.z);
}
bool	Undex3D::Box_exclusive(Undex3D idx, Undex3D min, Undex3D max)
{
	return	(idx.x > min.x && idx.x < max.x) &&
			(idx.y > min.y && idx.y < max.y) &&
			(idx.z > min.z && idx.z < max.z);
}



bool Undex3D::loop_inclusive(Undex3D & idx, Undex3D min, Undex3D max)
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
bool Undex3D::loop_exclusive(Undex3D & idx, Undex3D min, Undex3D max)
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
bool Undex3D::loop_inclusive(Undex3D & idx, unsigned int min, unsigned int max)
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
bool Undex3D::loop_exclusive(Undex3D & idx, unsigned int min, unsigned int max)
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





std::ostream & operator <<(std::ostream & o, const Undex3D & u)
{
	o << "[" << u.x << ":" << u.y << ":" << u.z << "]";
	return o;
}
