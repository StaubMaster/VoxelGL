
#include "openGL.h"

GLFWwindow *load_window(int w, int h, const char *name)
{
	if (!glfwInit())
	{
		write(2, "failed to glfw\n", 15);
		return (NULL);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow	*win;
	win = glfwCreateWindow(w, h, name, NULL, NULL);
	if (win == NULL)
	{
		write(2, "window NULL\n", 12);
		return (NULL);
	}
	glfwMakeContextCurrent(win);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(win);
		write(2, "failed to Load\n", 15);
		return (NULL);
	}
	glViewport(0, 0, w * 2, h * 2);

	return (win);
}

GLFWwindow *load_window_ReSize(int w, int h, const char *name)
{
	if (!glfwInit())
	{
		write(2, "failed to glfw\n", 15);
		return (NULL);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	GLFWwindow	*win;
	win = glfwCreateWindow(w, h, name, NULL, NULL);
	if (win == NULL)
	{
		write(2, "window NULL\n", 12);
		return (NULL);
	}
	glfwSetWindowAttrib(win, GLFW_RESIZABLE, GLFW_TRUE);

	glfwMakeContextCurrent(win);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(win);
		write(2, "failed to Load\n", 15);
		return (NULL);
	}

	return (win);
}
