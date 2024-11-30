
#include "Inventory.hpp"

InventoryForm::InventoryForm(Size2D winSize, int slots_x, int slots_y) : Form()
{
	//int	x_half = x / 2;
	//int	y_half = y / 2;

	//float	scale = 0.12f;
	//float	offset = 0.01f;

	(void)slots_x;
	(void)slots_y;

	/*Main.ChangeBox(Box2D(
		-x_half * scale - offset,
		-y_half * scale - offset,
		+x_half * scale + offset,
		+y_half * scale + offset
	));*/
	Main.ChangeBox(winSize, Box2D(
		200, 200, 800, 800
	));
	Main.AnchorBits = 0;
	//Main.AnchorBits = ANCHOR_BIT_L | ANCHOR_BIT_T;
	//Main.AnchorBits = ANCHOR_BIT_L | ANCHOR_BIT_T | ANCHOR_BIT_R | ANCHOR_BIT_B;

	slots_count = 0;
	/*slots = new FormSlot[x * y];
	for (int yi = -y_half; yi < +y_half; yi++)
	{
		for (int xi = -x_half; xi < +x_half; xi++)
		{
			slots[slots_count] = FormSlot(
				(xi * scale) + offset,
				(yi * scale) + offset,
				(xi * scale) + (scale - offset),
				(yi * scale) + (scale - offset)
			);
			Insert(slots[slots_count]);
			slots_count++;
		}
	}*/

	UpdateBuffer();
}
InventoryForm::~InventoryForm()
{
	//delete [] slots;
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
}

int		InventoryForm::getSlot(int idx) const
{
	return slots[idx].getItem();
}
void	InventoryForm::setSlot(int idx, int ID)
{
	slots[idx].setItem(ID);
}
