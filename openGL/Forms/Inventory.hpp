
#pragma once

#include "Controls/Form.hpp"
#include "Controls/Slot.hpp"

class	InventoryForm
{
	private:
		Form		form;
		FormSlot *	slots;
		int			slots_count;

	public:
		InventoryForm(int x, int y);
		~InventoryForm();

		void	Update(Point2D mouse);
		void	Click(int & ID);

		void	Draw() const;

		int		getSlot(int idx) const;
		void	setSlot(int idx, int ID);
};
