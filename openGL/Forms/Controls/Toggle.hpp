
#pragma once

#include "Control.hpp"

class FormToggle : public Control
{
	private:
		bool toggled;

	public:
		FormToggle();
		FormToggle(Box2D box);
		~FormToggle();

		void	UpdateHover(Point2D Mouse);

		void	UpdateRender();

		bool	Click();
		bool	Check();
};
