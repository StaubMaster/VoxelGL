
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "openGL/openGL.h"
#include "inst.cpp"

static void free_exit(GLFWwindow *win)
{
	inst_delete();
	glfwDestroyWindow(win);
	exit(EXIT_FAILURE);
}

static void	f_rot(float *pls, float *mns, float cos, float sin)
{
	float	temppp;
	temppp = pls[0] * cos - mns[0] * sin;
	mns[0] = mns[0] * cos + pls[0] * sin;
	pls[0] = temppp;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("needs texture name\n");
		return 0;
	}

	GLFWwindow	*win;
	win = load_window(1000, 1000, "cube");
	if (win == NULL)
		exit(EXIT_FAILURE);

	inst_init();
	if (inst_load_program() == 0)
		free_exit(win);

	inst_texture_gen();
	if (inst_texture_load(argv[1]) == 0)
		free_exit(win);

	inst_buffer_gen();
	{
		float Pos[] = (float[])
		{
			-1.0f, -1.0f, -1.0f, 0.75f, 0.99f,
			-1.0f, -1.0f, +1.0f, 1.00f, 0.99f,
			-1.0f, +1.0f, -1.0f, 0.75f, 0.50f,
			-1.0f, +1.0f, +1.0f, 1.00f, 0.50f,
			+1.0f, -1.0f, -1.0f, 0.50f, 0.99f,
			+1.0f, -1.0f, +1.0f, 0.25f, 0.99f,
			+1.0f, +1.0f, -1.0f, 0.50f, 0.50f,
			+1.0f, +1.0f, +1.0f, 0.25f, 0.50f,

			-1.0f, -1.0f, -1.0f, 0.25f, 0.99f,
			-1.0f, -1.0f, +1.0f, 0.50f, 0.99f,
			-1.0f, +1.0f, -1.0f, 0.25f, 0.50f,
			-1.0f, +1.0f, +1.0f, 0.50f, 0.50f,
			+1.0f, -1.0f, -1.0f, 0.00f, 0.99f,
			+1.0f, -1.0f, +1.0f, 0.75f, 0.99f,
			+1.0f, +1.0f, -1.0f, 0.00f, 0.50f,
			+1.0f, +1.0f, +1.0f, 0.75f, 0.50f,

			-1.0f, -1.0f, -1.0f, 0.50f, 0.00f,
			+1.0f, -1.0f, -1.0f, 0.25f, 0.00f,
			-1.0f, +1.0f, -1.0f, 0.75f, 0.50f,
			+1.0f, +1.0f, -1.0f, 0.50f, 0.50f,
			-1.0f, -1.0f, +1.0f, 0.50f, 0.50f,
			+1.0f, -1.0f, +1.0f, 0.25f, 0.50f,
			-1.0f, +1.0f, +1.0f, 0.75f, 0.00f,
			+1.0f, +1.0f, +1.0f, 0.50f, 0.00f,
		};
		inst_buffer_data_corn(Pos, 24);

		unsigned int Indexe[] = (unsigned int[])
		{
			0, 1, 2,    2, 1, 3,
			4, 6, 5,    5, 6, 7,

			0, 2, 4,    4, 2, 6,
			1, 5, 3,    3, 5, 7,

			0, 1, 4,    4, 1, 5,
			2, 6, 3,    3, 6, 7,
		};
		int i = 12 - 1;
		while (++i < 24)
			Indexe[i] += 8;
		i--;
		while (++i < 36)
			Indexe[i] += 16;
		inst_buffer_data_index(Indexe, 36);
	}

	unsigned int instances_count = 0xFFFF;
	t_inst_trans instances[instances_count];
	{
		instances -> pos_x = 0;
		instances -> pos_y = 0;
		instances -> pos_z = 0;
		instances -> ang_x = 0;
		instances -> ang_y = 0;
		instances -> ang_z = 0;
		inst_sin_cos(instances);

		float w;
		int i = 0;
		while (++i < instances_count)
		{
			instances[i].pos_x = ((rand() & 0xFF) + 15);
			instances[i].pos_y = (rand() & 0xFF) - 127;
			instances[i].pos_z = 0;

			w = rand();
			f_rot(&instances[i].pos_x, &instances[i].pos_z, cos(w), sin(w));
			instances[i].ang_x = (rand() & 0xFF);
			instances[i].ang_y = (rand() & 0xFF);
			instances[i].ang_z = (rand() & 0xFF);

			inst_sin_cos(&instances[i]);
		}
		inst_buffer_data_inst(instances, instances_count);
	}

	t_view view;
	view_init(&view, 0.5f, 0.03f);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	float angDist = 0.1f;
	float dist, ang;
	double last_frame = glfwGetTime();
	double time_diff;
	while (!glfwWindowShouldClose(win))
	{
		if (glfwGetKey(win, GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(win, 1); }

		time_diff = glfwGetTime() - last_frame;
		time_diff *= 60;
		last_frame = glfwGetTime();



		view_move_turn(&view, win);

		for (int i = 1; i < instances_count; i++)
		{
			dist = sqrt(
				(instances[i].pos_x * instances[i].pos_x) +
				(instances[i].pos_z * instances[i].pos_z));
			ang = angDist / dist;
			ang = ang * time_diff;
			f_rot(&instances[i].pos_x, &instances[i].pos_z, cos(ang), sin(ang));
			instances[i].ang_y += 0.01;
			inst_sin_cos(&instances[i]);
		}
		inst_buffer_data_inst(instances, instances_count);



		glClearColor(0.0f, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		inst_view(&view);
		inst_draw();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	glfwDestroyWindow(win);
	inst_delete();

	return (0);
}
