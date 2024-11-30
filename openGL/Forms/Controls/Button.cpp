
#include "Button.hpp"

FormButton::FormButton(float min_x, float min_y, float max_x, float max_y) :
	Control(min_x, min_y, max_x, max_y)
{
	
}
FormButton::~FormButton()
{

}



void	FormButton::UpdateHover(Point2D Mouse)
{
	Control::UpdateHover(Mouse);

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
}



void	FormButton::UpdateRender()
{
	if (render == NULL)
		return;
	render -> Col.R = 0.25;
	render -> Col.G = 0.25;
	render -> Col.B = 0.25;
	render -> Depth = 0.5f;
}
