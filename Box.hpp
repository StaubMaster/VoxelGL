
#ifndef BOX_HPP
# define BOX_HPP
# include "openGL/openGL.h"
# include "openGL/Abstract/math3D.hpp"
# include <iostream>

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

	public:
		Point	IntersektSize(Box & other);

	public:
		void	CreateBuffer();
		void	UpdateBuffer();
		void	Draw();
};

#endif
