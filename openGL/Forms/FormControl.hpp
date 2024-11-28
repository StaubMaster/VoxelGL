
#ifndef FORMCONTROL_HPP
# define FORMCONTROL_HPP
# include <vector>
# include "../openGL.h"
# include "../Shader.hpp"
# include "Window.hpp"

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

struct FormControlRenderData
{
	Point2D	Min;
	Point2D	Max;
	Color	Col;
	float	Depth;
};

class FormControl
{
	protected:
		Point2D	Min;
		Point2D	Max;

		FormControlRenderData * render;

	public:
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
	public:
		FormSlot(float min_x, float min_y, float max_x, float max_y);
		~FormSlot();

		Point2D	getCenter() const;
		void	Update(Point2D Mouse);

		void	UpdateRender();
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
