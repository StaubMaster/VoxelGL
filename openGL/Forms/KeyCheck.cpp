
#include "KeyCheck.hpp"

KeyCheck::KeyCheck(int key, bool isMouse) :
	key(key)
{
	if (isMouse)
		check_func = glfwGetMouseButton;
	else
		check_func = glfwGetKey;
}



KeyHold::KeyHold(int key, bool isMouse) : KeyCheck(key, isMouse)
{
	hold = false;
}
bool	KeyHold::check() const
{
	return hold;
}
void	KeyHold::update(GLFWwindow * win)
{
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



KeyPress::KeyPress(int key, bool isMouse) : KeyCheck(key, isMouse)
{
	press = false;
	hold = false;
}
bool	KeyPress::check() const
{
	return press;
}
void	KeyPress::update(GLFWwindow * win)
{
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

