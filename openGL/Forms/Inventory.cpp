
#include "Inventory.hpp"

InventoryForm::InventoryForm(Size2D winSize, int slots_x, int slots_y) : Form()
{
	int	x_half = slots_x / 2;
	int	y_half = slots_y / 2;

	float	scale = 50;
	float	offset = 5;

	Main.ChangeBox(Box2D(
		winSize.W / 2 - x_half * scale + offset / 2,
		winSize.H / 2 - y_half * scale + offset / 2,
		winSize.W / 2 + x_half * scale + offset / 2,
		winSize.H / 2 + y_half * scale + offset / 2 +
		scale + 10
	));
	Main.AnchorBits = 0;
	Main.ChangeAnchor(winSize, Point2D());

	slots_count = 0;
	slots = new FormSlot[slots_x * slots_y];
	for (int yi = 0; yi < slots_y; yi++)
	{
		for (int xi = 0; xi < slots_x; xi++)
		{
			slots[slots_count] = FormSlot(
				Main.Box.Min.X + xi * scale + (offset),
				Main.Box.Min.Y + yi * scale + (offset),
				Main.Box.Min.X + xi * scale + (scale - offset),
				Main.Box.Min.Y + yi * scale + (scale - offset)
			);
			slots[slots_count].AnchorBits = 0;
			slots[slots_count].ChangeAnchor(Main.Size, Main.Box.Min);
			Insert(slots[slots_count]);
			slots_count++;
		}
	}

	hots_count = 0;
	hots = new FormSlot[slots_x];
	for (int xi = 0; xi < slots_x; xi++)
	{
		hots[hots_count] = FormSlot(
			Main.Box.Min.X + xi * scale + (offset),
			Main.Box.Min.Y + slots_y * scale + (offset) + 10,
			Main.Box.Min.X + xi * scale + (scale - offset),
			Main.Box.Min.Y + slots_y * scale + (scale - offset) + 10
		);
		hots[hots_count].AnchorBits = 0;
		hots[hots_count].ChangeAnchor(Main.Size, Main.Box.Min);
		Insert(hots[hots_count]);
		hots_count++;
	}

	UpdateBuffer();
}
InventoryForm::~InventoryForm()
{
	delete [] hots;
	delete [] slots;
}

void	InventoryForm::Click(int & ID)
{
	for (int i = 0; i < slots_count; i++)
	{
		if (slots[i].isHover)
		{
			slots[i].SwapItem(ID);
			break;
		}
	}
 
	for (int i = 0; i < hots_count; i++)
	{
		if (hots[i].isHover)
		{
			hots[i].SwapItem(ID);
			break;
		}
	}
}

int		InventoryForm::getSlot(int idx) const
{
	return slots[idx].getItem();
}
void	InventoryForm::setSlot(int idx, int ID)
{
	slots[idx].setItem(ID);
}

int		InventoryForm::getHot(int idx) const
{
	return hots[idx].getItem();
}
void	InventoryForm::setHot(int idx, int ID)
{
	hots[idx].setItem(ID);
}
