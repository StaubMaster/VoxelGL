
#pragma once

#include "Controls/Form.hpp"
#include "Controls/Toggle.hpp"

class	DebugForm : public Form
{
	private:
		FormToggle *	toggles;
		int				toggles_count;

	public:
		DebugForm(Size2D winSize);
		~DebugForm();

		bool	Click();
};
