
#include "EntityBox.hpp"

EntityBox::EntityBox()
{

}
EntityBox::EntityBox(AxisBox box) :
	pos(), vel(), relBox(box)
{
	absBox.CreateBuffer();
}
EntityBox::~EntityBox()
{

}



void	EntityBox::Update(VoxelSpace & space, float time, Point move)
{
	vel = vel + (move * time);

	char	touchBits = space.TouchVoxel(absBox, 0.1f);

	if ((touchBits & AXIS_BIT_XN) && vel.x < 0) { vel.x = 0; }
	if ((touchBits & AXIS_BIT_XP) && vel.x > 0) { vel.x = 0; }
	if ((touchBits & AXIS_BIT_YN) && vel.y < 0) { vel.y = 0; }
	if ((touchBits & AXIS_BIT_YP) && vel.y > 0) { vel.y = 0; }
	if ((touchBits & AXIS_BIT_ZN) && vel.z < 0) { vel.z = 0; }
	if ((touchBits & AXIS_BIT_ZP) && vel.z > 0) { vel.z = 0; }

	if (!(touchBits & AXIS_BIT_YN))
	{
		//vel.y -= 0.01f;
	}
	else
	{
		//vel = vel * 0.999f;
	}
	vel = vel * 0.999f;

	float vel_len = vel.length();
	if (vel_len > 8.0f)
		vel = vel * (8.0f / vel_len);

	pos = pos + (vel * time);

	absBox.Min = pos + relBox.Min;
	absBox.Max = pos + relBox.Max;

	absBox.UpdateBuffer();
}

void	EntityBox::DrawBox()
{
	absBox.Draw();
}
