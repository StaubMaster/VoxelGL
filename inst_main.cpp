
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "openGL/openGL.h"
#include "openGL/Abstract/Angle.hpp"
#include "openGL/Forms/Window.hpp"
#include "openGL/Shader.hpp"
#include "openGL/View.hpp"
#include "VoxelChunk.hpp"
#include "VoxelSpace.hpp"
#include "Box.hpp"
//#include "inst.cpp"

/*static void use_info()
{
	std::cout
		<< "./a.out "
		<< "[texture.uints]"
		<< "\n";
}*/

int main(int argc, char **argv)
{
	/*if (argc != 2)
	{
		use_info();
		return 0;
	}*/

	Window * win = new Window(1000, 1000, "instance test", false);

/*
	inst_init();
	if (inst_load_program() == 0)
	{
		delete win;
	}
	std::cout << "instance program done\n";

	inst_texture_gen();
	if (inst_texture_load(argv[1]) == 0)
	{
		delete win;
	}
	std::cout << "individual textures done\n";

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
		std::cout << "  individual buffer vertex done\n";

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
		std::cout << "  individual buffer index done\n";
	}
	std::cout << "individual buffer done\n";

	unsigned int instances_count = 0xFF;
	std::cout << "instance size: " << sizeof(t_inst_trans) << "\n";
	std::cout << "instance array size: " << sizeof(t_inst_trans) * instances_count << "\n";
	t_inst_trans instances[instances_count];
	std::cout << "instance alloc done\n";
	{
		instances -> pos_x = 0;
		instances -> pos_y = 0;
		instances -> pos_z = 0;
		instances -> ang_x = 0;
		instances -> ang_y = 0;
		instances -> ang_z = 0;
		inst_sin_cos(instances);
		std::cout << "instance sin cos done\n";

		float w;
		unsigned int i = 0;
		while (++i < instances_count)
		{
			instances[i].pos_x = ((rand() & 0xF) + 64);
			//instances[i].pos_y = (rand() & 0xFF) - 127;
			instances[i].pos_z = 0;

			w = rand();
			Angle::rotate(instances[i].pos_x, instances[i].pos_z, cos(w), sin(w));
			instances[i].ang_x = (rand() & 0xFF);
			instances[i].ang_y = (rand() & 0xFF);
			instances[i].ang_z = (rand() & 0xFF);

			inst_sin_cos(&instances[i]);
		}
		inst_buffer_data_inst(instances, instances_count);
	}
	std::cout << "instance buffer done\n";
*/

	VoxelSpace space;
	space.FillRandom();
	Shader voxelShader(
		"shaders/chunk_vertex_project.vert",
		"shaders/faceNormalNoTex.geom",
		//"shaders/dirLightNoCol.frag"
		"shaders/depth.frag"
	);
	int Uni_Chunk_Pos = voxelShader.FindUniform("chunk_pos");
	int Uni_Chunk_View = voxelShader.FindUniform("view");
	int Uni_Chunk_Depth = voxelShader.FindUniform("depthFactor");
	std::cout << "Uni Chunk View " << Uni_Chunk_View << "\n";

	Shader boxShader(
		"shaders/Box.vert",
		"shaders/Box.geom",
		"shaders/simple.frag"
	);
	int Uni_Box_View = boxShader.FindUniform("view");
	int Uni_Box_Depth = boxShader.FindUniform("depthFactor");
	std::cout << "Uni Box View " << Uni_Box_View << "\n";

	Box box(Point(1, 2, 3), Point(4, 5, 6));
	box.CreateBuffer();
	box.UpdateBuffer();

	Shader rayShader(
		"shaders/Point.vert",
		"shaders/Fixed.frag"
	);
	int Uni_Ray_View = rayShader.FindUniform("view");
	std::cout << "Uni Ray View " << Uni_Ray_View << "\n";

	unsigned int Buffer_Array;
	unsigned int Buffer_Ray;
	glGenVertexArrays(1, &Buffer_Array);
	glGenBuffers(1, &Buffer_Ray);

	View view;

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	//float angDist = 0.1f;
	//float dist, ang;
	//double last_frame = glfwGetTime();
	//double time_diff;

	Point ray_pos(1.5, 4.5, 1.5);
	Point ray_dir(1, 0, 2);
	ray_dir = ray_dir / ray_dir.length();

	KeyPress voxel_add_key(GLFW_MOUSE_BUTTON_1, true);
	KeyPress voxel_sub_key(GLFW_MOUSE_BUTTON_2, true);
	win -> keys.push_back(&voxel_add_key);
	win -> keys.push_back(&voxel_sub_key);

	std::cout << "loop\n";
	while (!glfwWindowShouldClose(win -> win))
	{
		win -> Update();

		//time_diff = glfwGetTime() - last_frame;
		//time_diff *= 60;
		//last_frame = glfwGetTime();

		if (glfwGetKey(win -> win, GLFW_KEY_R))
		{
			space.FillRandom();
		}


		view.move(win -> GetKeyMovement(0.02f));
		//view.turn(win -> GetKeyTurning(0.03f));
		view.turn(win -> GetMouseTurning());

		/*for (unsigned int i = 1; i < instances_count; i++)
		{
			dist = sqrt(
				(instances[i].pos_x * instances[i].pos_x) +
				(instances[i].pos_z * instances[i].pos_z));
			ang = angDist / dist;
			ang = ang * time_diff;
			Angle::rotate(instances[i].pos_x, instances[i].pos_z, cos(ang), sin(ang));
			instances[i].ang_y += 0.01;
			inst_sin_cos(&instances[i]);
		}
		inst_buffer_data_inst(instances, instances_count);*/

		ray_pos = view.pos;
		ray_dir = view.ang.rotate_back(Point(0, 0, 1));
		VoxelSpace::Voxel_Hover hover;
		hover = space.Cross(ray_pos, ray_dir);
		if (voxel_add_key.check())
		{
			if (hover.isValid)
			{
				space.tryAdd(hover);
			}
		}
		if (voxel_sub_key.check())
		{
			if (hover.isValid)
			{
				space.trySub(hover);
			}
		}

		glClearColor(0.0f, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//inst_view((float *)&(view));
		//inst_draw();

		voxelShader.Use();
		view.uniform(Uni_Chunk_View);
		view.uniform_depth(Uni_Chunk_Depth);
		space.Draw(Uni_Chunk_Pos);

		boxShader.Use();
		view.uniform(Uni_Box_View);
		view.uniform_depth(Uni_Box_Depth);
		space.DrawHover(hover);


		Point ray[] = { ray_pos, ray_pos + (Point(-ray_dir.x, -ray_dir.y, +ray_dir.z) * 100) };


		rayShader.Use();
		view.uniform(Uni_Ray_View);
		glBindVertexArray(Buffer_Array);
		glBindBuffer(GL_ARRAY_BUFFER, Buffer_Ray);

		glBufferData(GL_ARRAY_BUFFER, 2 * 3 * sizeof(float), (float *)ray, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribIPointer(0, 3, GL_UNSIGNED_INT, 3 * sizeof(float), (void *)(0 * sizeof(float)));

		glDrawArrays(GL_LINES, 0, 2);



		glfwSwapBuffers(win -> win);
		glfwPollEvents();
	}
	delete win;
	//inst_delete();

	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Ray);
	glDeleteVertexArrays(1, &Buffer_Array);

	return (0);
	(void)argc;
	(void)argv;
}
