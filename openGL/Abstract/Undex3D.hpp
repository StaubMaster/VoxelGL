
#ifndef UNDEX3D_HPP
# define UNDEX3D_HPP

class Undex3D
{
	public:
		unsigned int x;
		unsigned int y;
		unsigned int z;

	public:
		Undex3D();
		Undex3D(unsigned int x, unsigned int y, unsigned int c);
		~Undex3D();
		Undex3D(const Undex3D & other);
		const Undex3D & operator =(const Undex3D & other);

		Undex3D operator +(const Undex3D & other) const;
		Undex3D operator -(const Undex3D & other) const;

	public:
		Undex3D Xn() const;
		Undex3D Xp() const;
		Undex3D Yn() const;
		Undex3D Yp() const;
		Undex3D Zn() const;
		Undex3D Zp() const;

		Undex3D	set_get_X(unsigned int new_x) const;
		Undex3D	set_get_Y(unsigned int new_y) const;
		Undex3D	set_get_Z(unsigned int new_z) const;

		static bool	Box_inclusive(Undex3D idx, Undex3D min, Undex3D max);
		static bool	Box_exclusive(Undex3D idx, Undex3D min, Undex3D max);

		static bool	loop(Undex3D & idx, Undex3D min, Undex3D max);
		static bool	loop(Undex3D & idx, unsigned int min, unsigned int max);
};

#endif
