
#ifndef WINDOW_HPP
# define WINDOW_HPP
# include "openGL.h"
# include "math3D.hpp"
# include <iostream>

class Window
{
	public:
		GLFWwindow *	win;
		bool			tabbed;
		bool			tabbed_pressed;

		double	win_middle_x;
		double	win_middle_y;

	private:
		Window();
	public:
		Window(int w, int h, const char * name);
		~Window();
	private:
		Window(const Window & other);
		void operator =(const Window & other);

	public:
		void	Update();
		Point GetKeyMovement(float speed) const;
		Angle GetKeyTurning(float speed) const;
		Angle GetMouseTurning() const;

	private:
		class GenericWindowException : public std::exception { public: const char * what() const throw(); };
};

#endif
