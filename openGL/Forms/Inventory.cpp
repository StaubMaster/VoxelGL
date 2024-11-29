
#include "Inventory.hpp"

InventoryForm::InventoryForm(int x, int y)
{
	int	x_half = x / 2;
	int	y_half = y / 2;

	float	scale = 0.12f;
	float	offset = 0.01f;

	form.ChangeMainSize(Box2D(
		-x_half * scale - offset,
		-y_half * scale - offset,
		+x_half * scale + offset,
		+y_half * scale + offset
	));

	slots = new FormSlot[x * y];
	slots_count = 0;
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
			form.Insert(slots[slots_count]);
			slots_count++;
		}
	}
	form.UpdateBuffer();
}
InventoryForm::~InventoryForm()
{
	delete [] slots;
}

void	InventoryForm::Update(Point2D mouse)
{
	form.Update(mouse);
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

void	InventoryForm::Draw() const
{
	form.Draw();
}

int		InventoryForm::getSlot(int idx) const
{
	return slots[idx].getItem();
}
void	InventoryForm::setSlot(int idx, int ID)
{
	slots[idx].setItem(ID);
}
