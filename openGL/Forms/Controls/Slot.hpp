
#pragma once

#include "Control.hpp"

#include "../ItemVoxel.hpp"

class FormSlot : public Control
{
	private:
		int	itemID;

	public:
		FormSlot();
		FormSlot(float min_x, float min_y, float max_x, float max_y);
		~FormSlot();

		Point2D	getCenter() const;
		void	Update(Point2D Mouse);

		void	UpdateRender();
		void	DrawExtra() const;

		void	SwapItem(int & ID);
		void	setItem(int ID);
		int		getItem();
};
