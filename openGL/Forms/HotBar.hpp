
#pragma once

#include "Controls/Form.hpp"
#include "Controls/Slot.hpp"
#include "Inventory.hpp"

class	HotbarForm
{
	private:
		Form		form;
		FormSlot *	slots;
		int			slots_count;

		int			selected;

	public:
		HotbarForm(int x);
		~HotbarForm();

		void	Inc();
		void	Dec();

		void	Draw() const;

		int		SelectedItem();
		void	Syncronize(InventoryForm & inv);
};
