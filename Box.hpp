
#ifndef BOX_HPP
# define BOX_HPP
# include "openGL/openGL.h"
# include "openGL/math3D.hpp"
# include <iostream>

class Box
{
	private:
		Point Min;
		Point Max;
	
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
		void	CreateBuffer();
		void	UpdateBuffer();
		void	Draw();
};

#endif
