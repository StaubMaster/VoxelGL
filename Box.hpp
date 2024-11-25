
#ifndef BOX_HPP
# define BOX_HPP
# include "openGL/openGL.h"
# include "openGL/Abstract/math3D.hpp"
# include <iostream>
# include <math.h>

# define AXIS_BIT_XN 0b000001
# define AXIS_BIT_YN 0b000010
# define AXIS_BIT_ZN 0b000100
# define AXIS_BIT_XP 0b001000
# define AXIS_BIT_YP 0b010000
# define AXIS_BIT_ZP 0b100000

class Box
{
	private:
	public:
		Point Min;
		Point Max;
	
	private:
		unsigned int	Buffer_Array;
		unsigned int	Buffer_MinMax;

	public:
		Box();
		Box(Point a, Point b);
		~Box();
	private:
		Box(const Box & other);
		const Box & operator =(const Box & other);

		Box	Move(Point rel) const;

	private:
		static bool		IntersektBoolX(const Box & b1, const Box & b2);
		static bool		IntersektBoolY(const Box & b1, const Box & b2);
		static bool		IntersektBoolZ(const Box & b1, const Box & b2);
	public:
		static bool		IntersektBool(const Box & b1, const Box & b2);

		static Point	IntersektDiff(const Box & b1, const Box & b2);
		static double	IntersektT(const Box & b1, const Box & b2, const Point v2);

		static char		TouchNeighbour(const Box & b1, const Box & b2, float d2);

	public:
		void	CreateBuffer();
		void	UpdateBuffer();
		void	Draw();
};

#endif
