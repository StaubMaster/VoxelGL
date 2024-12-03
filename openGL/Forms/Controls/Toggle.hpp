
#pragma once

#include "Control.hpp"

class ToggleControl : public Control
{
	private:
		bool toggled;

	public:
		ToggleControl();
		ToggleControl(Box2D box);
		~ToggleControl();

		void	UpdateHover(Point2D Mouse);

		void	UpdateRender();

		bool	Click();
		bool	Check();
};
