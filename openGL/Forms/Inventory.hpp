
#pragma once

#include "Controls/Form.hpp"
#include "Controls/Slot.hpp"

class	InventoryForm : public Form
{
	private:
		FormSlot *	slots;
		int			slots_count;

		FormSlot *	hots;
		int			hots_count;

	public:
		InventoryForm(Size2D winSize, int slots_x, int slots_y);
		~InventoryForm();

		void	Click(int & ID);

		int		getSlot(int idx) const;
		void	setSlot(int idx, int ID);

		int		getHot(int idx) const;
		void	setHot(int idx, int ID);
};
