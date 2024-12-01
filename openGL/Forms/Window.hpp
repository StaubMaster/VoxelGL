
#ifndef WINDOW_HPP
# define WINDOW_HPP
# include "KeyCheck.hpp"
# include "../openGL.h"
# include "../Abstract/math3D.hpp"
# include "Help.hpp"
# include <iostream>
# include <vector>

class Window
{
	public:
		GLFWwindow *	win;
		bool			tabbed;
		bool			tabbed_pressed;
		bool			sizeChanged;

		Size2D	Size;
		Size2D	Aspect;
		Point2D	Middle;

		std::vector<KeyCheck *>	keys;

	private:
		Window();
	public:
		Window(int w, int h, const char * name, bool resize);
		~Window();
	private:
		Window(const Window & other);
		void operator =(const Window & other);

	public:
		void	Update();
		Point GetKeyMovement(float speed) const;
		Angle GetKeyTurning(float speed) const;
		Angle GetMouseTurning();

		Point2D	CursorNormalized() const;
		Point2D	CursorRasterized() const;

		void	UniformAspect(int uni) const;
		void	UniformSize(int uni) const;

	private:
		class GenericWindowException : public std::exception { public: const char * what() const throw(); };
};

#endif
