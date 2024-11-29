
#ifndef CONTROL_HPP
# define CONTROL_HPP
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

	bool	check(Point2D p);
};



struct FormControlRenderData
{
	Box2D	Box;
	Color	Col;
	float	Depth;
};



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

class FormButton : public Control
{
	public:
		FormButton(float min_x, float min_y, float max_x, float max_y);
		~FormButton();

		void	Update(Point2D Mouse);

		void	UpdateRender();
};

class FormSlot : public Control
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
		void	DrawExtra() const;

		void	SwapItem(int & ID);
};

class Form
{
	public:
		static void CreateDraw();
		static void DeleteDraw();

	private:
		unsigned int Buffer_Array;
		unsigned int Buffer_Data;
		unsigned int Data_Count;

		Control	Main;

		std::vector<Control *> controls;
		std::vector<FormControlRenderData> renders;

	public:
		bool	Visible;

		Form();
		Form(Box2D box);
		~Form();
	private:
		Form(const Form & other);
		const Form & operator =(const Form & other);

	public:
		void	ChangeMainSize(Box2D box);

		void	Update(Point2D mouse);

		void	Insert(Control & control);

	public:
		void	UpdateBuffer();
		void	Draw() const;
};

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

#endif
