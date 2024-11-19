
#include <iostream>
#include <iomanip>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "openGL/openGL.h"
#include "openGL/textureLoadSave.h"
#include "openGL/Abstract/Angle.hpp"
#include "openGL/Forms/Window.hpp"
#include "openGL/Shader.hpp"
#include "openGL/View.hpp"
#include "VoxelChunk.hpp"
#include "VoxelSpace.hpp"
#include "Box.hpp"
#include "png/_png.h"
#include "png/PNG.hpp"

//#define TEXTURE_TEST

#ifdef TEXTURE_TEST
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		return 1;
	}

	//image img2 = load_png(argv[1]);
	//free(img2.data);
	//return 0;

	PNG_Image * img = load_png_better(argv[1]);

	Window * win = new Window(img -> w, img -> h, argv[1], false);
	std::cout << "window done\n";

	Shader texShader(
		"shaders/Tex.vert",
		"shaders/Tex.frag"
	);

	std::cout << "texture loading ...\n";
	unsigned int Texture0;
	glGenTextures(1, &Texture0);
	glBindTexture(GL_TEXTURE_2D, Texture0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img -> w, img -> h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, img -> data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	std::cout << "texture done\n";

	unsigned int Buffer_Array;
	unsigned int Buffer_Vertex;

	glGenVertexArrays(1, &Buffer_Array);
	glGenBuffers(1, &Buffer_Vertex);

	{
		float vertex_data[16] = {
			-1.0f, -1.0f, 0.0f, 1.0f,
			-1.0f, +1.0f, 0.0f, 0.0f,
			+1.0f, -1.0f, 1.0f, 1.0f,
			+1.0f, +1.0f, 1.0f, 0.0f,
		};

		glBindVertexArray(Buffer_Array);
		glBindBuffer(GL_ARRAY_BUFFER, Buffer_Vertex);

		glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertex_data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), (void *)(0 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	}

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	std::cout << "loop\n\n\n\n\n\n\n";
	while (!glfwWindowShouldClose(win -> win))
	{
		win -> Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1);

		texShader.Use();
		glBindVertexArray(Buffer_Array);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE0, Texture0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glfwSwapBuffers(win -> win);
		glfwPollEvents();
	}

	glDeleteTextures(1, &Texture0);

	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Vertex);
	glDeleteVertexArrays(1, &Buffer_Array);

	delete win;
	//free(img.data);
	delete img;

	return 0;
}
#endif

#ifndef TEXTURE_TEST
int main(int argc, char **argv)
{
	Window * win = new Window(1000, 1000, "Voxel", false);
	std::cout << "window done\n";

	Shader voxelShader(
		//"shaders/chunk_vertex_project.vert",
		//"shaders/faceNormalNoTex.geom",
		//"shaders/depthLightNoCol.frag"
		"shaders/voxel_project_tex.vert",
		"shaders/voxel_normal_tex.geom",
		"shaders/voxel_depth_tex.frag"
	);
	int Uni_Chunk_View = voxelShader.FindUniform("viewTrans");
	int Uni_Chunk_Depth = voxelShader.FindUniform("depthFactor");
	int Uni_Chunk_Pos = voxelShader.FindUniform("chunk_pos");

	Shader boxShader(
		"shaders/Box.vert",
		"shaders/Box.geom",
		"shaders/Cycle.frag"
	);
	int Uni_Box_View = boxShader.FindUniform("viewTrans");
	int Uni_Box_Depth = boxShader.FindUniform("depthFactor");
	int Uni_Box_Cycle = boxShader.FindUniform("cycle");

	{
		std::cout << "General Info\n";
		std::cout << "  Memory:\n";
		std::cout << "    per Chunks:\n";
		std::cout << "      Voxels: " << mem_size_1000_original(Voxel_per_Chunk * sizeof(Voxel)) << "\n";
		std::cout << "      Buffer: " << mem_size_1000_original(Vertex_per_Chunk * 6 * 6 * sizeof(Voxel::RenderData)) << "\n";
		//std::cout << "      Vertex Buffer Limit: " << mem_size_1000_original(Vertex_per_Chunk * sizeof(float)) << "\n";
		//std::cout << "      Index Buffer Limit: " << mem_size_1000_original(Voxel_per_Chunk * sizeof(unsigned int) * 6 * 3) << "\n";
	}

	std::cout << "texture loading ...\n";
	unsigned int Texture0;
	glGenTextures(1, &Texture0);
	glBindTexture(GL_TEXTURE_2D, Texture0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	{
		//int w, h;
		//unsigned int *texData;
		//texture_load("textures/cube_face_log.uints", &texData, &w, &h);
		//texture_load("textures/cube_face_col.uints", &texData, &w, &h);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, texData);
		//free(texData);

		PNG_Image * img = load_png_better(argv[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img -> w, img -> h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, img -> data);
		delete img;

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	std::cout << "texture done\n";

	View view;
	//view.pos.z = -(128 + 10);
	VoxelSpace space;


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

	std::cout << "loop\n\n\n\n\n\n\n";
	while (!glfwWindowShouldClose(win -> win))
	{
		win -> Update();


		view.move(win -> GetKeyMovement(0.005f));
		//view.turn(win -> GetKeyTurning(0.03f));
		view.turn(win -> GetMouseTurning());


		Index3D chunk_current;
		chunk_current.x = floorf(view.pos.x / Voxel_per_Side);
		chunk_current.y = floorf(view.pos.y / Voxel_per_Side);
		chunk_current.z = floorf(view.pos.z / Voxel_per_Side);

		space.AddChunksRange(chunk_current, 1);
		space.SubChunksRange(chunk_current, 1);

		VoxelSpace::Voxel_Hover hover;
		hover = space.Cross(view.pos, view.ang.rotate_back(Point(0, 0, 1)));
		if (voxel_add_key.check() && hover.isValid)
			space.tryAdd(hover);
		if (voxel_sub_key.check() && hover.isValid)
			space.trySub(hover);



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1);


		voxelShader.Use();
		view.uniform(Uni_Chunk_View);
		view.uniform_depth(Uni_Chunk_Depth);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE0, Texture0);
		space.Draw(Uni_Chunk_Pos);

		boxShader.Use();
		glUniform1f(Uni_Box_Cycle, glfwGetTime() * 16);
		view.uniform(Uni_Box_View);
		view.uniform_depth(Uni_Box_Depth);
		space.DrawHover(hover);
		//space.DrawBound();


		glfwSwapBuffers(win -> win);
		glfwPollEvents();
	}

	glDeleteTextures(1, &Texture0);
	delete win;

	(void)Uni_Box_Cycle;
	(void)Uni_Box_View;
	(void)Uni_Box_Depth;

	return (0);
	(void)argc;
	(void)argv;
}
#endif
