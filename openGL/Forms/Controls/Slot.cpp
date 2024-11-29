
#include "Slot.hpp"

FormSlot::FormSlot() :
	Control()
{
	itemID = -1;
}
FormSlot::FormSlot(float min_x, float min_y, float max_x, float max_y) :
	Control(min_x, min_y, max_x, max_y)
{
	itemID = -1;
}
FormSlot::~FormSlot()
{

}



Point2D	FormSlot::getCenter() const
{
	return Point2D(
		(Box.Min.X + Box.Max.X) / 2,
		(Box.Min.Y + Box.Max.Y) / 2
	);
}
void	FormSlot::Update(Point2D Mouse)
{
	Control::Update(Mouse);
	UpdateRender();
}



void	FormSlot::UpdateRender()
{
	if (render == NULL)
		return;

	if (isHover)
	{
		render -> Col.R = 0.85;
		render -> Col.G = 0.85;
		render -> Col.B = 0.85;
	}
	else
	{
		render -> Col.R = 0.75;
		render -> Col.G = 0.75;
		render -> Col.B = 0.75;
	}

	render -> Depth = 0.5f;
}
void	FormSlot::DrawExtra() const
{
	if (itemID == -1) { return; }
	Point2D center = getCenter();
	ItemVoxel::Draw(center.X, center.Y, itemID);
}



void	FormSlot::SwapItem(int & ID)
{
	int temp = ID;
	ID = itemID;
	itemID = temp;
}
void	FormSlot::setItem(int ID)
{
	itemID = ID;
}
int	FormSlot::getItem()
{
	return (itemID);
}
