
#pragma once

#include "Help.hpp"

class Control
{
	protected:
		Box2D	Box;
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

		void			ChangeBox(Box2D box);

		virtual void	Update(Point2D Mouse);

		virtual void			UpdateRender();
		FormControlRenderData	getRenderData() const;
		void					setRenderData(FormControlRenderData * ptr);
		virtual void			DrawExtra() const;
};
