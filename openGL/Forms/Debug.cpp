
#include "Debug.hpp"

DebugForm::DebugForm(Size2D winSize) : Form()
{
	float	scale = 50;
	float	offset = 5;

	Main.ChangeBox(Box2D(
		0, 250, 250, 750
	));
	Main.AnchorBits = ANCHOR_BIT_L;
	Main.ChangeAnchor(winSize, Point2D());

	toggles_count = 0;
	toggles = new ToggleControl[10];
	labels_count = 0;
	labels = new TextControl[10];
	for (int yi = 0; yi < 10; yi++)
	{
		toggles[toggles_count] = ToggleControl(Box2D(
			Main.L() + offset,
			Main.T() + offset + yi * scale,
			Main.L() + (scale - offset),
			Main.T() + yi * scale + (scale - offset)
		));
		toggles[toggles_count].AnchorBits = 0;
		toggles[toggles_count].ChangeAnchor(Main.Size, Main.Box.Min);
		Insert(toggles[toggles_count]);
		Control & tog = toggles[toggles_count];
		toggles_count++;

		labels[labels_count] = TextControl(Box2D(
			tog.R() + offset,
			tog.T(),
			Main.R() - offset,
			tog.B()
		));
		labels[labels_count].AnchorBits = 0;
		labels[labels_count].ChangeAnchor(Main.Size, Main.Box.Min);
		Insert(labels[labels_count]);
		labels_count++;
	}
	UpdateBuffer();

	labels[0].UpdateText(text_buffer, "FPS");
	labels[1].UpdateText(text_buffer, "Time");
	labels[2].UpdateText(text_buffer, "Space Mem");
	text_buffer.UpdateBuffer();
}
DebugForm::~DebugForm()
{
	delete [] toggles;
	delete [] labels;
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
bool	DebugForm::Check(int idx)
{
	if (idx < 0 || idx >= toggles_count)
		return false;
	return toggles[idx].Check();
}

void	DebugForm::DrawText()
{
	if (!Visible) { return; }
	text_buffer.Draw();
}
