
#include "KeyCheck.hpp"

KeyCheck::KeyCheck(int key) : key(key)
{

}



KeyPress::KeyPress(int key) : KeyCheck(key)
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
		if (glfwGetKey(win, key) == GLFW_RELEASE)
		{
			hold = false;
		}
	}
	else
	{
		if (glfwGetKey(win, key) == GLFW_PRESS)
		{
			press = true;
			hold = true;
		}
	}
}

