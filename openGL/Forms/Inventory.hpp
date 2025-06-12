
#pragma once

#include "Controls/Form.hpp"
#include "Controls/Slot.hpp"

class	InventoryForm : public Form
{
	private:
		SlotControl *	slots;
		int			slots_count;

		SlotControl *	hots;
		int			hots_count;

	public:
		InventoryForm(Size2D winSize, int slots_x, int slots_y);
		~InventoryForm();

		bool	Click(int & ID);

		int		getSlot(int idx) const;
		void	setSlot(int idx, int ID);

		int		getHot(int idx) const;
		void	setHot(int idx, int ID);
};
