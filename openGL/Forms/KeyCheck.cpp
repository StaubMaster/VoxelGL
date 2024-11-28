
#include "KeyCheck.hpp"

KeyCheck::KeyCheck(int key, bool isMouse, bool isTabbed) :
	key(key), Tabbed(isTabbed)
{
	if (isMouse)
		check_func = glfwGetMouseButton;
	else
		check_func = glfwGetKey;
}



KeyHold::KeyHold(int key, bool isMouse, bool isTabbed) : KeyCheck(key, isMouse, isTabbed)
{
	hold = false;
}
bool	KeyHold::check() const
{
	return hold;
}
void	KeyHold::update(GLFWwindow * win, bool tabbed)
{
	if (tabbed != Tabbed) { return; }

	if (hold)
	{
		if (check_func(win, key) == GLFW_RELEASE)
		{
			hold = false;
		}
	}
	else
	{
		if (check_func(win, key) == GLFW_PRESS)
		{
			hold = true;
		}
	}
}



KeyPress::KeyPress(int key, bool isMouse, bool isTabbed) : KeyCheck(key, isMouse, isTabbed)
{
	press = false;
	hold = false;
}
bool	KeyPress::check() const
{
	return press;
}
void	KeyPress::update(GLFWwindow * win, bool tabbed)
{
	if (tabbed != Tabbed) { return; }

	if (hold)
	{
		press = false;
		if (check_func(win, key) == GLFW_RELEASE)
		{
			hold = false;
		}
	}
	else
	{
		if (check_func(win, key) == GLFW_PRESS)
		{
			press = true;
			hold = true;
		}
	}
}

