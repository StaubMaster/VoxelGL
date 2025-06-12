
#include "Button.hpp"

ButtonControl::ButtonControl(Box2D box) :
	Control(box)
{
}
ButtonControl::~ButtonControl()
{

}



void	ButtonControl::UpdateHover(Point2D Mouse)
{
	Control::UpdateHover(Mouse);
	UpdateRender();
}



void	ButtonControl::UpdateRender()
{
	if (render == NULL)
		return;

	if (isHover)
	{
		render -> Col.R = 0.25;
		render -> Col.G = 0.75;
		render -> Col.B = 0.25;
	}
	else
	{
		render -> Col.R = 0.25;
		render -> Col.G = 0.25;
		render -> Col.B = 0.25;
	}

	render -> Depth = 0.5f;
}
