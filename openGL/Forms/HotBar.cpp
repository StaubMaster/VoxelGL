
#include "Hotbar.hpp"

HotbarForm::HotbarForm(int x)
{
	int	x_half = x / 2;

	float	scale = 0.12f;
	float	offset = 0.01f;

	Main.ChangeBox(Size2D(), Box2D(
		-x_half * scale - offset,
		-8 * scale - offset,
		+x_half * scale + offset,
		-7 * scale + offset
	));

	slots = new FormSlot[x];
	slots_count = 0;
	int yi = -8;
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
		slots[i].setItem(inv.getSlot(i));
		slots[i].UpdateRender();
	}
	UpdateBuffer();
}
