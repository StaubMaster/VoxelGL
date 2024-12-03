
#pragma once

#include "Controls/Form.hpp"
#include "Controls/Toggle.hpp"
#include "Controls/Text.hpp"

class	DebugForm : public Form
{
	private:
		ToggleControl *	toggles;
		int				toggles_count;

		TextControl *	labels;
		int				labels_count;

		BufferString	text_buffer;

	public:
		DebugForm(Size2D winSize);
		~DebugForm();

		bool	Click();
		bool	Check(int idx);

		void	DrawText();
};
