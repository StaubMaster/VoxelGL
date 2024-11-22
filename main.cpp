
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

#include "Voxel/VoxelChunk.hpp"
#include "Voxel/VoxelSpace.hpp"

#include "Box.hpp"

#include "FileParse/PNG/PNG_Image.hpp"

float interpolate(float v0, float v1, float t)
{
	return (v0 * (t - 0)) + (v1 * (1 - t));
}

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
		std::cout << "      Buffer: " << mem_size_1000_original(Vertex_per_Chunk * 6 * 6 * sizeof(VoxelRenderData)) << "\n";
	}

	std::cout << "texture loading ...\n";
	unsigned int Texture0 = 0;
	{
		glGenTextures(1, &Texture0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, Texture0);
		glActiveTexture(GL_TEXTURE0);

		const char * file_names[] = {
			"images/TextureAlign.png",
			"images/fancy_GreenDirt.png",
			"images/fancy_RedWood.png",
			"images/fancy_BlueSpiral.png",
			"images/BlueSpiral.png",
		};

		int	tex_w = 128;
		int	tex_h = 64;
		int	img_count = 5;

		PNG_Image ** img = new PNG_Image * [img_count];
		for (int i = 0; i < img_count; i++)
		{
			img[i] = PNG_Image::Load(file_names[i]);
		}

		for (int i = 0; i < img_count; i++)
		{
			PNG_Image * temp = img[i] -> Scale(tex_w, tex_h);
			delete img[i];
			img[i] = temp;
		}

		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8,   tex_w, tex_h, img_count, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, NULL);
		for (int i = 0; i < img_count; i++)
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, tex_w, tex_h, 1, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, img[i] -> data);

		for (int i = 0; i < img_count; i++)
			delete img[i];
		delete [] img;

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
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

	double	FrameTimeLast = glfwGetTime();
	double	FrameTimeCurr;
	double	FrameTimeDelta;

	char	placeID = 0;
	KeyPress place_add_key(GLFW_MOUSE_BUTTON_4, true);
	KeyPress place_sub_key(GLFW_MOUSE_BUTTON_5, true);
	win -> keys.push_back(&place_add_key);
	win -> keys.push_back(&place_sub_key);

	std::cout << "loop\n\n\n\n\n\n\n";
	while (!glfwWindowShouldClose(win -> win))
	{
		win -> Update();

		FrameTimeCurr = glfwGetTime();
		FrameTimeDelta = FrameTimeCurr - FrameTimeLast;
		FrameTimeLast = FrameTimeCurr;


		view.move(win -> GetKeyMovement(5.0f * FrameTimeDelta));
		//view.turn(win -> GetKeyTurning(0.03f));
		view.turn(win -> GetMouseTurning());

		if (place_add_key.check())
		{
			placeID++;
			if (placeID > 4) { placeID = 0; }
		}
		if (place_sub_key.check())
		{
			placeID--;
			if (placeID < 0) { placeID = 4; }
		}


		Index3D chunk_current;
		chunk_current.x = floorf(view.pos.x / Voxel_per_Side);
		chunk_current.y = floorf(view.pos.y / Voxel_per_Side);
		chunk_current.z = floorf(view.pos.z / Voxel_per_Side);

		space.AddChunksRange(chunk_current, 1);
		space.SubChunksRange(chunk_current, 1);

		VoxelSpace::Voxel_Hover hover;
		hover = space.Cross(view.pos, view.ang.rotate_back(Point(0, 0, 1)));
		if (voxel_add_key.check() && hover.isValid)
			space.tryAdd(hover, placeID);
		if (voxel_sub_key.check() && hover.isValid)
			space.trySub(hover, placeID);



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1);


		voxelShader.Use();
		view.uniform(Uni_Chunk_View);
		view.uniform_depth(Uni_Chunk_Depth);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE0, Texture0);
		//glActiveTexture(GL_TEXTURE_2D_ARRAY);
		//glBindTexture(GL_TEXTURE_2D_ARRAY, Texture0);
		space.Draw(Uni_Chunk_Pos);

		boxShader.Use();
		glUniform1f(Uni_Box_Cycle, FrameTimeCurr * 16);
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
