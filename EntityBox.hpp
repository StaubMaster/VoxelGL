
#ifndef ENTIRYBOX_HPP
# define ENTIRYBOX_HPP
# include <iostream>

# include "./openGL/Abstract/Point.hpp"

# include "./Grid/Space/VoxelSpace.hpp"

# include "./AxisBox.hpp"

class EntityBox
{
	private:
	public:
		Point	pos;
		Point	vel;
		AxisBox	relBox;
		AxisBox	absBox;

	public:
		EntityBox();
		EntityBox(AxisBox box);
		~EntityBox();

	public:
		void	Update(VoxelSpace & space, float time, Point move);

		void	DrawBox();
};

#endif
