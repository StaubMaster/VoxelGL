
#pragma once

#include "Control.hpp"

class ButtonControl : public Control
{
	public:
		ButtonControl(Box2D box);
		~ButtonControl();

		void	UpdateHover(Point2D Mouse);

		void	UpdateRender();
};
