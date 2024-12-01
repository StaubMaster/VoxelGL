
#include "Debug.hpp"

DebugForm::DebugForm(Size2D winSize) : Form()
{
	float	scale = 50;
	float	offset = 5;

	Main.ChangeBox(Box2D(
		//winSize.W / 2 - x_half * scale + offset / 2,
		//winSize.H / 2 - y_half * scale + offset / 2,
		//winSize.W / 2 + x_half * scale + offset / 2,
		//winSize.H / 2 + y_half * scale + offset / 2 +
		//scale + 10
		0, 250, 250, 750
	));
	Main.AnchorBits = ANCHOR_BIT_L;
	Main.ChangeAnchor(winSize, Point2D());

	toggles_count = 0;
	toggles = new FormToggle[10];
	for (int yi = 0; yi < 10; yi++)
	{
		{
			toggles[toggles_count] = FormToggle(Box2D(
				//Main.Box.Min.X + xi * scale + (offset),
				//Main.Box.Min.Y + yi * scale + (offset),
				//Main.Box.Min.X + xi * scale + (scale - offset),
				//Main.Box.Min.Y + yi * scale + (scale - offset)
				Main.Box.Min.X + offset,
				Main.Box.Min.Y + offset + yi * scale,
				Main.Box.Min.X + (scale - offset),
				Main.Box.Min.Y + yi * scale + (scale - offset)
			));
			toggles[toggles_count].AnchorBits = 0;
			toggles[toggles_count].ChangeAnchor(Main.Size, Main.Box.Min);
			Insert(toggles[toggles_count]);
			toggles_count++;
		}
	}

	UpdateBuffer();
}
DebugForm::~DebugForm()
{
	delete [] toggles;
}

bool	DebugForm::Click()
{
	for (int i = 0; i < toggles_count; i++)
	{
		if (toggles[i].Click())
		{
			UpdateBuffer();
			return (true);
		}
	}
	return (false);
}
