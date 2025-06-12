
#ifndef INDEX3D_HPP
# define INDEX3D_HPP

# include <iostream>

# include "Point.hpp"

class Index3D
{
	public:
		int x;
		int y;
		int z;

	public:
		Index3D();
		Index3D(int i);
		Index3D(int x, int y, int c);
		~Index3D();
		Index3D(const Index3D & other);
		const Index3D & operator =(const Index3D & other);

		Index3D operator +(const Index3D & other) const;
		Index3D operator -(const Index3D & other) const;

		int	ToIndex(int size_per_side) const;

	public:
		Index3D Xn() const;
		Index3D Xp() const;
		Index3D Yn() const;
		Index3D Yp() const;
		Index3D Zn() const;
		Index3D Zp() const;

		static bool	Box_inclusive(Index3D idx, Index3D min, Index3D max);
		static bool	Box_exclusive(Index3D idx, Index3D min, Index3D max);

		static bool	loop_inclusive(Index3D & idx, Index3D min, Index3D max);
		static bool	loop_exclusive(Index3D & idx, Index3D min, Index3D max);
		static bool	loop_inclusive(Index3D & idx, int min, int max);
		static bool	loop_exclusive(Index3D & idx, int min, int max);

		void	Clamp(int min, int max);

		static Index3D	Floor(Point p);
		static Index3D	Ceil(Point p);
};

std::ostream & operator <<(std::ostream & o, const Index3D & idx);

#endif
