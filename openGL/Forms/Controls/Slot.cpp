
#include "Slot.hpp"

SlotControl::SlotControl() :
	Control()
{
	itemID = -1;
}
SlotControl::SlotControl(float min_x, float min_y, float max_x, float max_y) :
	Control(min_x, min_y, max_x, max_y)
{
	itemID = -1;
}
SlotControl::~SlotControl()
{

}



Point2D	SlotControl::getCenter() const
{
	return Point2D(
		(Box.Min.X + Box.Max.X) / 2,
		(Box.Min.Y + Box.Max.Y) / 2
	);
}
void	SlotControl::UpdateHover(Point2D Mouse)
{
	Control::UpdateHover(Mouse);
	UpdateRender();
}



void	SlotControl::UpdateRender()
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
void	SlotControl::DrawExtra() const
{
	if (itemID == -1) { return; }
	Point2D center = getCenter();
	ItemVoxel::Draw(center.X, center.Y, itemID);
}



void	SlotControl::SwapItem(int & ID)
{
	int temp = ID;
	ID = itemID;
	itemID = temp;
}
void	SlotControl::setItem(int ID)
{
	itemID = ID;
}
int	SlotControl::getItem()
{
	return (itemID);
}
