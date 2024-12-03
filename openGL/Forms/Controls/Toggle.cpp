
#include "Toggle.hpp"

ToggleControl::ToggleControl() :
	Control()
{

}
ToggleControl::ToggleControl(Box2D box) :
	Control(box)
{
	toggled = false;
}
ToggleControl::~ToggleControl()
{

}



void	ToggleControl::UpdateHover(Point2D Mouse)
{
	Control::UpdateHover(Mouse);
	UpdateRender();
}



void	ToggleControl::UpdateRender()
{
	if (render == NULL)
		return;

	if (!toggled)
	{
		if (!isHover)
		{
			render -> Col.R = 0.75;
			render -> Col.G = 0.00;
		}
		else
		{
			render -> Col.R = 0.50;
			render -> Col.G = 0.25;
		}
	}
	else
	{
		if (!isHover)
		{
			render -> Col.R = 0.00;
			render -> Col.G = 0.75;
		}
		else
		{
			render -> Col.R = 0.25;
			render -> Col.G = 0.50;
		}
	}
	render -> Col.B = 0.00;

	render -> Depth = 0.5f;
}



bool	ToggleControl::Click()
{
	if (!isHover) { return false; }
	toggled = !toggled;
	UpdateRender();
	return true;
}
bool	ToggleControl::Check()
{
	return toggled;
}
