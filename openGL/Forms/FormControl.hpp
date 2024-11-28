
#ifndef FORMCONTROL_HPP
# define FORMCONTROL_HPP
# include <vector>
# include "../openGL.h"
# include "../Shader.hpp"
# include "Window.hpp"
# include "ItemVoxel.hpp"

struct	Point2D
{
	float	X;
	float	Y;

	Point2D();
	Point2D(float x, float y);
};

struct	Color
{
	float	R;
	float	G;
	float	B;

	Color(float r, float g, float b);
};

struct	Box2D
{
	Point2D	Min;
	Point2D	Max;

	Box2D();
	Box2D(float x1, float y1, float x2, float y2);
	Box2D(Point2D p1, Point2D p2);
};

struct FormControlRenderData
{
	Box2D	Box;
	Color	Col;
	float	Depth;
};

class FormControl
{
	protected:
		Box2D	Box;

		FormControlRenderData * render;

	public:
		FormControl();
		FormControl(float min_x, float min_y, float max_x, float max_y);
		virtual ~FormControl();

		FormControl(const FormControl & other);
		const FormControl & operator =(const FormControl & other);

		bool			isHover(Point2D Mouse) const;
		virtual void	Update(Point2D Mouse);

		virtual void			UpdateRender();
		FormControlRenderData	getRenderData() const;
		void					setRenderData(FormControlRenderData * ptr);
};

class FormButton : public FormControl
{
	public:
		FormButton(float min_x, float min_y, float max_x, float max_y);
		~FormButton();

		void	Update(Point2D Mouse);

		void	UpdateRender();
};

class FormSlot : public FormControl
{
	private:
		int	itemID;

	public:
		FormSlot();
		FormSlot(float min_x, float min_y, float max_x, float max_y);
		~FormSlot();

		Point2D	getCenter() const;
		void	Update(Point2D Mouse);

		void	UpdateRender();

		void	SwapItem(int & ID);
		void	DrawItem();
};

class FormControlList
{
	private:
		Shader	* shader;
		unsigned int Buffer_Array;
		unsigned int Buffer_Data;
		unsigned int Data_Count;

		std::vector<FormControl *> controls;
		std::vector<FormControlRenderData> renders;

	public:
		FormControlList();
		~FormControlList();

		void	Update(Window * win);

		void	Insert(FormControl & control);

		void	UpdateBuffer();
		void	Draw() const;
};

#endif
