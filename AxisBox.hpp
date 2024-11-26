
#ifndef AXISBOX_HPP
# define AXISBOX_HPP
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

class AxisBox
{
	private:
	public:
		Point Min;
		Point Max;
	
	private:
		unsigned int	Buffer_Array;
		unsigned int	Buffer_MinMax;

	public:
		AxisBox();
		AxisBox(Point a, Point b);
		~AxisBox();

		AxisBox(const AxisBox & other);
	private:
		const AxisBox & operator =(const AxisBox & other);

		AxisBox	Move(Point rel) const;

	private:
		static bool		IntersektBoolX(const AxisBox & b1, const AxisBox & b2);
		static bool		IntersektBoolY(const AxisBox & b1, const AxisBox & b2);
		static bool		IntersektBoolZ(const AxisBox & b1, const AxisBox & b2);
	public:
		static bool		IntersektBool(const AxisBox & b1, const AxisBox & b2);

		static Point	IntersektDiff(const AxisBox & b1, const AxisBox & b2);
		static double	IntersektT(const AxisBox & b1, const AxisBox & b2, const Point v2);

		static char		TouchBits(const AxisBox & b1, const AxisBox & b2, float d2);

	public:
		void	CreateBuffer();
		void	UpdateBuffer();
		void	Draw();
};

#endif
