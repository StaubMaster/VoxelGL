
#include <iostream>
#include <iomanip>

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

int main(int argc, char **argv)
{
	Window * win = new Window(1000, 1000, "instance test", false);

	Shader voxelShader(
		"shaders/chunk_vertex_project.vert",
		"shaders/faceNormalNoTex.geom",
		"shaders/depthLightNoCol.frag"
	);
	int Uni_Chunk_View = voxelShader.FindUniform("viewTrans");
	int Uni_Chunk_Depth = voxelShader.FindUniform("depthFactor");
	int Uni_Chunk_Pos = voxelShader.FindUniform("chunk_pos");

	Shader boxShader(
		"shaders/Box.vert",
		"shaders/Box.geom",
		"shaders/simple.frag"
	);
	int Uni_Box_View = boxShader.FindUniform("viewTrans");
	int Uni_Box_Depth = boxShader.FindUniform("depthFactor");



	View view;

	VoxelSpace space;
	space.FillRandom();



	KeyPress voxel_add_key(GLFW_MOUSE_BUTTON_1, true);
	KeyPress voxel_sub_key(GLFW_MOUSE_BUTTON_2, true);
	win -> keys.push_back(&voxel_add_key);
	win -> keys.push_back(&voxel_sub_key);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	space.AddChunksRange(Index3D(), 3);

	std::cout << "loop\n\n\n\n\n\n\n";
	while (!glfwWindowShouldClose(win -> win))
	{
		win -> Update();


		view.move(win -> GetKeyMovement(0.005f));
		//view.turn(win -> GetKeyTurning(0.03f));
		view.turn(win -> GetMouseTurning());


		Index3D chunk_current;
		chunk_current.x = floorf(view.pos.x / VoxelChunk::Voxel_per_Side);
		chunk_current.y = floorf(view.pos.y / VoxelChunk::Voxel_per_Side);
		chunk_current.z = floorf(view.pos.z / VoxelChunk::Voxel_per_Side);

		double t1, t2, t3;

		t1 = glfwGetTime();
		space.AddChunksRange(chunk_current, 3);
		t2 = glfwGetTime();
		space.SubChunksRange(chunk_current, 3);
		t3 = glfwGetTime();

		VoxelSpace::Voxel_Hover hover;
		hover = space.Cross(view.pos, view.ang.rotate_back(Point(0, 0, 1)));
		if (voxel_add_key.check() && hover.isValid)
			space.tryAdd(hover);
		if (voxel_sub_key.check() && hover.isValid)
			space.trySub(hover);



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.25f, 0.0f, 0.0f, 1);


		voxelShader.Use();
		view.uniform(Uni_Chunk_View);
		view.uniform_depth(Uni_Chunk_Depth);
		double t4, t5;
		t4 = glfwGetTime();
		space.Draw(Uni_Chunk_Pos);
		t5 = glfwGetTime();

		boxShader.Use();
		view.uniform(Uni_Box_View);
		view.uniform_depth(Uni_Box_Depth);
		double t6, t7;
		t6 = glfwGetTime();
		space.DrawHover(hover);
		t7 = glfwGetTime();
		//space.DrawBound();


		glfwSwapBuffers(win -> win);
		glfwPollEvents();

		std::cout
			<< "\e[6A\n"
			<< std::fixed << std::setprecision(8)
			<< "add   " << ((t2 - t1)) << "s\n"
			<< "sub   " << ((t3 - t2)) << "s\n"
			<< "space " << ((t5 - t4)) << "s\n"
			<< "hover " << ((t7 - t6)) << "s\n"
			<< "\n";
		(void)t1;
		(void)t2;
		(void)t3;
		(void)t4;
		(void)t5;
		(void)t6;
		(void)t7;
	}
	delete win;

	return (0);
	(void)argc;
	(void)argv;
}
