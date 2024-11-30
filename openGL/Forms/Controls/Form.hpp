
#pragma once

#include "Control.hpp"

#include <vector>
#include "../../openGL.h"
#include "../../Shader.hpp"

class Form
{
	public:
		static void CreateDraw();
		static void DeleteDraw();
		static int  UniformAspect();
		static int  UniformSize();

	private:
		unsigned int Buffer_Array;
		unsigned int Buffer_Data;
		unsigned int Data_Count;

	protected:
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
		void	UpdateHover(Point2D mouse);
		void	UpdateAnchor(Size2D winSize);

		void	Insert(Control & control);

	public:
		void	UpdateBuffer();
		void	Draw() const;
};
