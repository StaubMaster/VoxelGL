
#pragma once

#include "Control.hpp"

class FormButton : public Control
{
	public:
		FormButton(float min_x, float min_y, float max_x, float max_y);
		~FormButton();

		void	Update(Point2D Mouse);

		void	UpdateRender();
};
