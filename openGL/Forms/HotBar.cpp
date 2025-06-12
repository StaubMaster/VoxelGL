
#include "HotBar.hpp"

HotbarForm::HotbarForm(Size2D winSize, int slots_x)
{
	int	x_half = slots_x / 2;

	float	scale = 50;
	float	offset = 5;

	Main.ChangeBox(Box2D(
		winSize.W / 2 - x_half * scale + offset / 2,
		winSize.H - offset - scale + offset / 2,
		winSize.W / 2 + x_half * scale + offset / 2,
		winSize.H - offset + offset / 2
	));
	Main.AnchorBits = ANCHOR_BIT_B;
	Main.ChangeAnchor(winSize, Point2D());

	slots = new SlotControl[slots_x];
	slots_count = 0;
	for (int xi = 0; xi < slots_x; xi++)
	{
		slots[slots_count] = SlotControl(
			Main.Box.Min.X + xi * scale + (offset),
			Main.Box.Min.Y + (offset),
			Main.Box.Min.X + xi * scale + (scale - offset),
			Main.Box.Min.Y + (scale - offset)
		);
		slots[slots_count].AnchorBits = 0;
		slots[slots_count].ChangeAnchor(Main.Size, Main.Box.Min);
		Insert(slots[slots_count]);
		slots_count++;
	}

	selected = 0;
	slots[selected].isHover = true;
	slots[selected].UpdateRender();

	UpdateBuffer();
}
HotbarForm::~HotbarForm()
{
	delete [] slots;
}

void	HotbarForm::Inc()
{
	slots[selected].isHover = false;
	slots[selected].UpdateRender();

	selected++;
	if (selected == slots_count) { selected = 0; }

	slots[selected].isHover = true;
	slots[selected].UpdateRender();

	UpdateBuffer();
}
void	HotbarForm::Dec()
{
	slots[selected].isHover = false;
	slots[selected].UpdateRender();

	if (selected == 0) { selected = slots_count; }
	selected--;

	slots[selected].isHover = true;
	slots[selected].UpdateRender();

	UpdateBuffer();
}

int		HotbarForm::SelectedItem()
{
	return slots[selected].getItem();
}
void	HotbarForm::Syncronize(InventoryForm & inv)
{
	for (int i = 0; i < slots_count; i++)
	{
		slots[i].setItem(inv.getHot(i));
		slots[i].UpdateRender();
	}
	UpdateBuffer();
}
