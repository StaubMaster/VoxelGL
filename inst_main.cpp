
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "openGL/openGL.h"
#include "openGL/Window.hpp"
#include "openGL/View.hpp"
#include "VoxelChunk.hpp"
#include "inst.cpp"

static void free_exit(GLFWwindow *win)
{
	inst_delete();
	(void)win;
	exit(EXIT_FAILURE);
}

static void	f_rot(float *pls, float *mns, float cos, float sin)
{
	float	temppp;
	temppp = pls[0] * cos - mns[0] * sin;
	mns[0] = mns[0] * cos + pls[0] * sin;
	pls[0] = temppp;
}

static void use_info()
{
	std::cout
		<< "./a.out "
		<< "[texture.uints]"
		<< "\n";
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		(void)argc;
		(void)argv;
		use_info();
		return 0;
	}

	Window * win = new Window(1000, 1000, "instance test");

	inst_init();
	if (inst_load_program() == 0)
		free_exit(NULL);
	std::cout << "inst prog done\n";

	inst_texture_gen();
	if (inst_texture_load(argv[1]) == 0)
		free_exit(NULL);
	std::cout << "inst tex done\n";

	inst_buffer_gen();
	{
		float Pos[] =
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

		unsigned int Indexe[] =
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
		unsigned int i = 0;
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
	std::cout << "inst buff done\n";

	VoxelChunk chunk;
	chunk.UpdateBufferCorner();
	chunk.UpdateBufferIndex();
	Shader voxelShader(
		"shaders/tri_project.vert",
		"shaders/faceNormalNoTex.geom",
		"shaders/dirLightNoCol.frag"
	);
	unsigned int Uni_View = voxelShader.FindUniform("view");
	std::cout << "view Uni " << Uni_View << "\n";

	View view;

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

	std::cout << "loop\n";
	while (!glfwWindowShouldClose(win -> win))
	{
		win -> Update();

		time_diff = glfwGetTime() - last_frame;
		time_diff *= 60;
		last_frame = glfwGetTime();


		view.move(win -> GetKeyMovement(0.5f));
		//view.turn(win -> GetKeyTurning(0.03f));
		view.turn(win -> GetMouseTurning());

		for (unsigned int i = 1; i < instances_count; i++)
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

		inst_view((float *)&(view));
		//inst_draw();

		voxelShader.Use();
		glUniform3fv(Uni_View, 3, (float *)&view);
		chunk.Draw();

		glfwSwapBuffers(win -> win);
		glfwPollEvents();
	}
	delete win;
	inst_delete();

	return (0);
}
