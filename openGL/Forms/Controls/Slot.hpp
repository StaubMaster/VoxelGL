
#pragma once

#include "Control.hpp"

#include "../ItemVoxel.hpp"

class SlotControl : public Control
{
	private:
		int	itemID;

	public:
		SlotControl();
		SlotControl(float min_x, float min_y, float max_x, float max_y);
		~SlotControl();

		Point2D	getCenter() const;
		void	UpdateHover(Point2D Mouse);

		void	UpdateRender();
		void	DrawExtra() const;

		void	SwapItem(int & ID);
		void	setItem(int ID);
		int		getItem();
};
