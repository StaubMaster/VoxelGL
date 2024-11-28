
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
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
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

	int ww, hh;
	glfwGetFramebufferSize(win, &ww, &hh);
	std::cout << w << ":" << h << "\n";
	std::cout << ww << ":" << hh << "\n";
	glViewport(0, 0, ww, hh);
//#ifdef _WIN64
//	glViewport(0, 0, w, h);			//Windows
//#elif __APPLE__
//	glViewport(0, 0, w * 2, h * 2);	//	Mac
//#endif
	std::cout << "gl viewport done\n";

	tabbed = false;
	tabbed_pressed = false;

	win_middle_x = w * 0.5;
	win_middle_y = h * 0.5;
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
Angle Window::GetMouseTurning() const
{
	if (!tabbed)
		return Angle();

	double x, y;
	glfwGetCursorPos(win, &x, &y);

	double diff_x, diff_y;
	diff_x = win_middle_x - x;
	diff_y = win_middle_y - y;

	Angle ang;
	ang.x -= diff_x * 0.005;
	ang.y += diff_y * 0.005;
	ang.UpdateSinCos();
	glfwSetCursorPos(win, win_middle_x, win_middle_y);

	return (ang);
}


const char * Window::GenericWindowException::what() const throw() { return "Error from Window"; }
