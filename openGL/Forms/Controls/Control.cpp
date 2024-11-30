
#include "Control.hpp"

Control::Control() :
	Box(),
	Size(),
	render(NULL)
{

}
Control::Control(float min_x, float min_y, float max_x, float max_y) :
	Box(min_x, min_y, max_x, max_y),
	Size(max_x - min_x, max_y - min_y),
	render(NULL),
	isHover(false)
{

}
Control::Control(Box2D box) :
	Box(box),
	Size(box.Max.X - box.Min.X, box.Max.Y - box.Min.Y),
	render(NULL),
	isHover(false)
{

}
Control::~Control()
{

}
Control::Control(const Control & other) :
	Box(other.Box),
	Size(other.Size.W, other.Size.H),
	render(other.render),
	isHover(other.isHover)
{

}
const Control & Control::operator =(const Control & other)
{
	Box = other.Box;
	Size = other.Size;
	render = other.render;
	isHover = other.isHover;
	return *this;
}



void	Control::ChangeBox(Size2D formSize, Box2D box)
{
	Box = box;
	Size.W = Box.Max.X - Box.Min.X;
	Size.H = Box.Max.Y - Box.Min.Y;

	Anchor_L = Box.Min.X;
	Anchor_T = Box.Min.Y;
	Anchor_R = formSize.W - Box.Max.X;
	Anchor_B = formSize.H - Box.Max.Y;

	if (render != NULL)
	{
		render -> Box = Box;
	}
}



void	Control::UpdateHover(Point2D Mouse)
{
	isHover = Box.check(Mouse);
}
void	Control::UpdateAnchor(Size2D formSize)
{
	if (AnchorBits & ANCHOR_BIT_L)
	{
		Box.Min.X = Anchor_L;
		render -> Box.Min.X = Box.Min.X;
	}

	if (AnchorBits & ANCHOR_BIT_T)
	{
		Box.Min.Y = Anchor_T;
		render -> Box.Min.Y = Box.Min.Y;
	}

	if (AnchorBits & ANCHOR_BIT_R)
	{
		Box.Max.X = formSize.W - Anchor_R;
		render -> Box.Max.X = Box.Max.X;
	}
	else
	{
		Box.Max.X = Box.Min.X + Size.W;
		render -> Box.Max.X = Box.Max.X;
	}

	if (AnchorBits & ANCHOR_BIT_B)
	{
		Box.Max.Y = formSize.H - Anchor_B;
		render -> Box.Max.Y = Box.Max.Y;
	}
	else
	{
		Box.Max.Y = Box.Min.Y + Size.H;
		render -> Box.Max.Y = Box.Max.Y;
	}

	(void)formSize;
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
