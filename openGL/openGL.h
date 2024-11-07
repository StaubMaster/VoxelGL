
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

int	load_programVF(const char *vert, const char *frag);
int	load_programVGF(const char *vert, const char *geom, const char *frag);

void texture_save(const char *name, unsigned int *data, int w, int h);
void texture_load(const char *name, unsigned int **data, int *w, int *h);


typedef struct s_view
{
	float	pos_x, pos_y, pos_z;
	float	sin_x, sin_y, sin_z;
	float	cos_x, cos_y, cos_z;
	float	ang_x, ang_y, ang_z;
	float	*data;
	float	move_speed;
	float	turn_speed;
}	t_view;
void	view_init(t_view *view, float move, float turn);
void	view_move_turn(t_view *view, GLFWwindow *win);
void	view_uniform(t_view *view, int uni);


#endif
