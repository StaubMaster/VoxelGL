
#ifndef FORMCONTROL_HPP
# define FORMCONTROL_HPP
# include <vector>
# include "../openGL.h"
# include "../Shader.hpp"
# include "Window.hpp"

struct FormControlRenderData
{
	float	MinX;
	float	MinY;

	float	MaxX;
	float	MaxY;

	float	ColR;
	float	ColG;
	float	ColB;

	float	Depth;
};

class FormControl
{
	protected:
		float	MinX;
		float	MinY;

		float	MaxX;
		float	MaxY;

		FormControlRenderData * render;

	public:
		FormControl(float min_x, float min_y, float max_x, float max_y);
		virtual ~FormControl();

		FormControl(const FormControl & other);
		const FormControl & operator =(const FormControl & other);

		bool			isHover(float mouse_x, float mouse_y) const;
		virtual void	Update(float mouse_x, float mouse_y);

		virtual void			UpdateRender();
		FormControlRenderData	getRenderData() const;
		void					setRenderData(FormControlRenderData * ptr);
};

class FormButton : public FormControl
{
	public:
		FormButton(float min_x, float min_y, float max_x, float max_y);
		~FormButton();

		void	Update(float mouse_x, float mouse_y);

		void	UpdateRender();
};

class FormSlot : public FormControl
{
	public:
		FormSlot(float min_x, float min_y, float max_x, float max_y);
		~FormSlot();

		void	Update(float mouse_x, float mouse_y);

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
