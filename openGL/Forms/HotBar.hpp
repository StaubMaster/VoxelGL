
#pragma once

#include "Controls/Form.hpp"
#include "Controls/Slot.hpp"
#include "Inventory.hpp"

class	HotbarForm : public Form
{
	private:
		FormSlot *	slots;
		int			slots_count;

		int			selected;

	public:
		HotbarForm(int x);
		~HotbarForm();

		void	Inc();
		void	Dec();

		int		SelectedItem();
		void	Syncronize(InventoryForm & inv);
};
