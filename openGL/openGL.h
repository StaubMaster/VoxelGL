
#ifndef OPENGL_H
# define OPENGL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# include "glad.h"
# include <GLFW/glfw3.h>

GLFWwindow *load_window(int w, int h, const char *name);
GLFWwindow *load_window_ReSize(int w, int h, const char *name);

#endif
