
#include "Window.hpp"

Window::Window::Window()
{
	throw GenericWindowException();
}
Window::Window(int w, int h, const char * name, bool resize)
{
	if (!glfwInit())
	{
		std::cout << "failed to glfw\n";
		throw GenericWindowException();
	}
	std::cout << "glfw done\n";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	win = glfwCreateWindow(w, h, name, NULL, NULL);
	if (win == NULL)
	{
		std::cout << "glfw window NULL\n";
		throw GenericWindowException();
	}
	glfwSetWindowAttrib(win, GLFW_RESIZABLE, resize);
	std::cout << "glfw window done\n";

	glfwMakeContextCurrent(win);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(win);
		std::cout << "glad failed\n";
		throw GenericWindowException();
	}
	std::cout << "glad done\n";

	glfwGetFramebufferSize(win, &w, &h);
	glViewport(0, 0, w, h);
	std::cout << "gl viewport done\n";

	tabbed = false;
	tabbed_pressed = false;

	Size.X = w;
	Size.Y = h;

	float	aspect_size;
	aspect_size = std::min(w, h);

	Aspect.X = aspect_size / w;
	Aspect.Y = aspect_size / h;

	Middle.X = w * 0.5;
	Middle.Y = h * 0.5;
}
Window::~Window()
{
	glfwDestroyWindow(win);
}
Window::Window(const Window & other)
{
	(void)other;
	throw GenericWindowException();
}
void Window::operator =(const Window & other)
{
	(void)other;
	throw GenericWindowException();
}



void Window::Update()
{
	if (glfwGetKey(win, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(win, 1);
	}

	if (glfwGetKey(win, GLFW_KEY_TAB))
	{
		if (!tabbed_pressed)
		{
			tabbed = !tabbed;
		}
		tabbed_pressed = true;
	}
	else
	{
		tabbed_pressed = false;
	}

	for (size_t i = 0; i < keys.size(); i++)
	{
		keys[i] -> update(win, tabbed);
	}

	int new_w, new_h;
	glfwGetFramebufferSize(win, &new_w, &new_h);

	if (new_w != Size.X || new_h != Size.Y)
	{
		glViewport(0, 0, new_w, new_h);
		Size.X = new_w;
		Size.Y = new_h;

		float	aspect_size;
		aspect_size = std::min(new_w, new_h);

		Aspect.X = aspect_size / new_w;
		Aspect.Y = aspect_size / new_h;

		Middle.X = (int)(Size.X * 0.5);
		Middle.Y = (int)(Size.Y * 0.5);
	}
}
Point Window::GetKeyMovement(float speed) const
{
	Point rel;
	if (glfwGetKey(win, GLFW_KEY_A))			{ rel.x -= speed; }
	if (glfwGetKey(win, GLFW_KEY_D))			{ rel.x += speed; }
	if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT))	{ rel.y -= speed; }
	if (glfwGetKey(win, GLFW_KEY_SPACE))		{ rel.y += speed; }
	if (glfwGetKey(win, GLFW_KEY_S))			{ rel.z -= speed; }
	if (glfwGetKey(win, GLFW_KEY_W))			{ rel.z += speed; }
	return (rel);
}
Angle Window::GetKeyTurning(float speed) const
{
	Angle rel;
	if (glfwGetKey(win, GLFW_KEY_DOWN))		{ rel.x += speed; }
	if (glfwGetKey(win, GLFW_KEY_UP))		{ rel.x -= speed; }
	if (glfwGetKey(win, GLFW_KEY_LEFT))		{ rel.y += speed; }
	if (glfwGetKey(win, GLFW_KEY_RIGHT))	{ rel.y -= speed; }
	return (rel);
}
Angle Window::GetMouseTurning()
{
	if (!tabbed)
		return Angle();

	double x, y;
	glfwGetCursorPos(win, &x, &y);

	double diff_x, diff_y;
	diff_x = Middle.X - x;
	diff_y = Middle.Y - y;

	Angle ang;
	ang.x -= diff_x * 0.005;
	ang.y += diff_y * 0.005;
	ang.UpdateSinCos();
	glfwSetCursorPos(win, Middle.X, Middle.Y);

	return (ang);
}



Point2D	Window::CursorNormalized() const
{
	double	mouse_x_dbl;
	double	mouse_y_dbl;
	glfwGetCursorPos(win, &mouse_x_dbl, &mouse_y_dbl);

	return Point2D(
		2 * (mouse_x_dbl / Size.X) - 1,
		1 - (mouse_y_dbl / Size.Y) * 2
	);
}
Point2D	Window::CursorRasterized() const
{
	double	mouse_x_dbl;
	double	mouse_y_dbl;
	glfwGetCursorPos(win, &mouse_x_dbl, &mouse_y_dbl);

	return Point2D(
		mouse_x_dbl,
		mouse_y_dbl
	);
}



void	Window::UniformAspect(int uni) const
{
	glUniform2f(uni, Aspect.X, Aspect.Y);
}
void	Window::UniformSize(int uni) const
{
	glUniform2f(uni, Size.X, Size.Y);
}



const char * Window::GenericWindowException::what() const throw() { return "Error from Window"; }
