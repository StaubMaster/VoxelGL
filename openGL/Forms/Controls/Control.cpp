
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



void	Control::ChangeAnchor(Size2D formSize, Point2D formPos)
{
	Anchor_L = Box.Min.X - formPos.X;
	Anchor_T = Box.Min.Y - formPos.Y;
	Anchor_R = formSize.W - (Box.Max.X - formPos.X);
	Anchor_B = formSize.H - (Box.Max.Y - formPos.Y);
}
void	Control::ChangeBox(Box2D box)
{
	Box = box;

	Size.W = Box.Max.X - Box.Min.X;
	Size.H = Box.Max.Y - Box.Min.Y;

	if (render != NULL)
	{
		render -> Box = Box;
	}
}



void	Control::UpdateHover(Point2D Mouse)
{
	isHover = Box.check(Mouse);
}
void	Control::UpdateAnchor(Size2D formSize, Point2D formPos)
{
	if ((AnchorBits & ANCHOR_BIT_L) && (AnchorBits & ANCHOR_BIT_R))
	{
		Box.Min.X = Anchor_L;
		Box.Max.X = formSize.W - Anchor_R;
	}
	else if (AnchorBits & ANCHOR_BIT_L)
	{
		Box.Min.X = Anchor_L;
		Box.Max.X = Box.Min.X + Size.W;
	}
	else if (AnchorBits & ANCHOR_BIT_R)
	{
		Box.Max.X = formSize.W - Anchor_R;
		Box.Min.X = Box.Max.X - Size.W;
	}
	else
	{
		Box.Min.X = ((Anchor_L + formSize.W) - (Anchor_R + Size.W)) / 2;
		Box.Max.X = Box.Min.X + Size.W;
	}

	if ((AnchorBits & ANCHOR_BIT_T) && (AnchorBits & ANCHOR_BIT_B))
	{
		Box.Min.Y = Anchor_T;
		Box.Max.Y = formSize.H - Anchor_B;
	}
	else if (AnchorBits & ANCHOR_BIT_T)
	{
		Box.Min.Y = Anchor_T;
		Box.Max.Y = Box.Min.Y + Size.H;
	}
	else if (AnchorBits & ANCHOR_BIT_B)
	{
		Box.Max.Y = formSize.H - Anchor_B;
		Box.Min.Y = Box.Max.Y - Size.H;
	}
	else
	{
		Box.Min.Y = ((Anchor_T + formSize.H) - (Anchor_B + Size.H)) / 2;
		Box.Max.Y = Box.Min.Y + Size.H;
	}

	Box.Min.X += formPos.X;
	Box.Min.Y += formPos.Y;
	Box.Max.X += formPos.X;
	Box.Max.Y += formPos.Y;

	render -> Box = Box;
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
