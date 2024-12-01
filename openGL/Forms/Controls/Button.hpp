
#pragma once

#include "Control.hpp"

class FormButton : public Control
{
	public:
		FormButton(Box2D box);
		~FormButton();

		void	UpdateHover(Point2D Mouse);

		void	UpdateRender();
};
