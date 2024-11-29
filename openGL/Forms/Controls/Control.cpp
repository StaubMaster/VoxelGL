
#include "Control.hpp"

Control::Control() :
	Box(),
	render(NULL)
{

}
Control::Control(float min_x, float min_y, float max_x, float max_y) :
	Box(min_x, min_y, max_x, max_y),
	render(NULL),
	isHover(false)
{

}
Control::Control(Box2D box) :
	Box(box),
	render(NULL),
	isHover(false)
{

}
Control::~Control()
{

}
Control::Control(const Control & other) :
	Box(other.Box),
	render(other.render),
	isHover(other.isHover)
{

}
const Control & Control::operator =(const Control & other)
{
	Box = other.Box;
	render = other.render;
	isHover = other.isHover;
	return *this;
}



void	Control::ChangeBox(Box2D box)
{
	Box = box;
	if (render != NULL)
	{
		render -> Box = Box;
	}
}



void	Control::Update(Point2D Mouse)
{
	isHover = Box.check(Mouse);
}



void	Control::UpdateRender()
{
	if (render == NULL)
		return;
}
FormControlRenderData	Control::getRenderData() const
{
	return (FormControlRenderData) {
		Box,
		Color(0.5f, 0.5f, 0.5f),
		0.99f
	};
}
void	Control::setRenderData(FormControlRenderData * ptr)
{
	render = ptr;
}
void	Control::DrawExtra() const
{
	
}
