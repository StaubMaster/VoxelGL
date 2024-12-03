
#pragma once

#include "../Help.hpp"

#define ANCHOR_BIT_L 0b0001
#define ANCHOR_BIT_T 0b0010
#define ANCHOR_BIT_R 0b0100
#define ANCHOR_BIT_B 0b1000

/*
	Point2D		Pos		top left
	Size2D		Size	size going down and right

	Box2D		Box		actual Box that encompassed the Control

	Box2D		FormDist	distance of each Control Side to the Form

	Duplicates:
		Pos and Box.Min and FormDist.Min are the same

		Box.Min = Pos
		Box.Max = Pos + Size

		FormDist.Min = Pos
		FormDist.Max = Form.Size - Box.Max

	Anchor()
	when anchored to a side
	upon size change, this control side distance should stay the same
	example:
		distance
*/

class Control
{
	public:
		char	AnchorBits;
		float	Anchor_L;
		float	Anchor_T;
		float	Anchor_R;
		float	Anchor_B;

		Box2D	Box;
		Size2D	Size;
	protected:
		FormControlRenderData * render;

	public:
		bool	isHover;

	public:
		Control();
		Control(float min_x, float min_y, float max_x, float max_y);
		Control(Box2D box);
		virtual ~Control();

		Control(const Control & other);
		const Control & operator =(const Control & other);

		float	L() const;
		float	T() const;
		float	R() const;
		float	B() const;

		void			ChangeAnchor(Size2D formSize, Point2D formPos);
		void			ChangeBox(Box2D box);

		virtual void	UpdateHover(Point2D Mouse);
		void			UpdateAnchor(Size2D formSize, Point2D formPos);

		virtual void			UpdateRender();
		FormControlRenderData	getRenderData() const;
		void					setRenderData(FormControlRenderData * ptr);
		virtual void			DrawExtra() const;
};
