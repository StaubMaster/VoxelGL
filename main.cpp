
#include <sstream>
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

#include "AxisBox.hpp"
#include "EntityBox.hpp"

#include "FileParse/PNG/PNG_Image.hpp"

float interpolate(float v0, float v1, float t)
{
	return (v0 * (t - 0)) + (v1 * (1 - t));
}

int main(int argc, char **argv)
{
	std::cout << "window ...\n";
	Window * win = new Window(1000, 1000, "Voxel", false);
	std::cout << "window done\n";

	std::cout << "shaders ...\n";
	Shader voxelShader(
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

	Shader inventoryShader(
		"shaders/inventory.vert",
		"shaders/inventory.geom",
		"shaders/inventory.frag"
	);
	int Uni_Inv_Pos = inventoryShader.FindUniform("UPos");
	int Uni_Inv_Spin = inventoryShader.FindUniform("USpin");
	int Uni_Inv_TexIdx = inventoryShader.FindUniform("UTex_Idx");
	std::cout << "shaders done\n";

	Angle Inv_Spin(1, 0.5, 0);

	unsigned int Inv_Buffer_Array;
	unsigned int Inv_Buffer_Vertex;
	unsigned int Inv_Render_Data_Count = 36;
	float Inv_Render_Data[] =
	{
		-0.1f, -0.1f, -0.1f, 0.25f, 1.0f,
		-0.1f, -0.1f, +0.1f, 0.25f, 0.5f,
		-0.1f, +0.1f, -0.1f, 0.00f, 1.0f,
		-0.1f, +0.1f, -0.1f, 0.00f, 1.0f,
		-0.1f, -0.1f, +0.1f, 0.25f, 0.5f,
		-0.1f, +0.1f, +0.1f, 0.00f, 0.5f,

		-0.1f, -0.1f, -0.1f, 0.50f, 1.0f,
		+0.1f, -0.1f, -0.1f, 0.50f, 0.5f,
		-0.1f, -0.1f, +0.1f, 0.25f, 1.0f,
		-0.1f, -0.1f, +0.1f, 0.25f, 1.0f,
		+0.1f, -0.1f, -0.1f, 0.50f, 0.5f,
		+0.1f, -0.1f, +0.1f, 0.25f, 0.5f,

		-0.1f, -0.1f, -0.1f, 0.75f, 1.0f,
		-0.1f, +0.1f, -0.1f, 0.75f, 0.5f,
		+0.1f, -0.1f, -0.1f, 0.50f, 1.0f,
		+0.1f, -0.1f, -0.1f, 0.50f, 1.0f,
		-0.1f, +0.1f, -0.1f, 0.75f, 0.5f,
		+0.1f, +0.1f, -0.1f, 0.50f, 0.5f,

		+0.1f, -0.1f, -0.1f, 0.25f, 0.5f,
		+0.1f, +0.1f, -0.1f, 0.00f, 0.5f,
		+0.1f, -0.1f, +0.1f, 0.25f, 0.0f,
		+0.1f, -0.1f, +0.1f, 0.25f, 0.0f,
		+0.1f, +0.1f, -0.1f, 0.00f, 0.5f,
		+0.1f, +0.1f, +0.1f, 0.00f, 0.0f,

		-0.1f, +0.1f, -0.1f, 0.50f, 0.5f,
		-0.1f, +0.1f, +0.1f, 0.25f, 0.5f,
		+0.1f, +0.1f, -0.1f, 0.50f, 0.0f,
		+0.1f, +0.1f, -0.1f, 0.50f, 0.0f,
		-0.1f, +0.1f, +0.1f, 0.25f, 0.5f,
		+0.1f, +0.1f, +0.1f, 0.25f, 0.0f,

		-0.1f, -0.1f, +0.1f, 0.75f, 0.5f,
		+0.1f, -0.1f, +0.1f, 0.50f, 0.5f,
		-0.1f, +0.1f, +0.1f, 0.75f, 0.0f,
		-0.1f, +0.1f, +0.1f, 0.75f, 0.0f,
		+0.1f, -0.1f, +0.1f, 0.50f, 0.5f,
		+0.1f, +0.1f, +0.1f, 0.50f, 0.0f,
	};
	glGenVertexArrays(1, &Inv_Buffer_Array);
	glGenBuffers(1, &Inv_Buffer_Vertex);
	glBindVertexArray(Inv_Buffer_Array);
	glBindBuffer(GL_ARRAY_BUFFER, Inv_Buffer_Vertex);
	glBufferData(GL_ARRAY_BUFFER, Inv_Render_Data_Count * sizeof(float) * 5, Inv_Render_Data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, (void *)(sizeof(float) * 3));

	std::cout << "table ...\n";
	VoxelDataTable table;
	table.Set(VoxelData("images/TextureAlign.png",     false, false, false, true , false));
	table.Set(VoxelData("images/fancy_GreenDirt.png",  false, false, false, false, false));
	table.Set(VoxelData("images/fancy_RedWood.png",    false, false, false, true , false));
	table.Set(VoxelData("images/fancy_BlueSpiral.png", false, false, true , false, false));
	table.Set(VoxelData("images/BlueSpiral.png",       false, false, false, false, false));
	table.Set(VoxelData("images/Window.png",           false, false, true , false, false));
	table.Set(VoxelData("images/fancy_RedPlank.png",   false, false, false, true , true ));
	table.Set(VoxelData("images/Brick.png",            false, false, false, true , false));
	std::cout << "table done\n";

	std::cout << "textures ...\n";
	unsigned int texture_arr = table.InitTextures();
	std::cout << "textures done\n";

	View view;
	//view.pos.z = -(128 + 10);
	VoxelSpace space(table);


	KeyPress test_Box_Key(GLFW_KEY_Q, false);
	win -> keys.push_back(&test_Box_Key);


	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	KeyPress voxel_add_key(GLFW_MOUSE_BUTTON_1, true);
	KeyPress voxel_sub_key(GLFW_MOUSE_BUTTON_2, true);
	win -> keys.push_back(&voxel_add_key);
	win -> keys.push_back(&voxel_sub_key);

	double	FrameTimeLast = glfwGetTime();
	double	FrameTimeCurr;
	double	FrameTimeDelta;

	char	placeID = 0;
	KeyPress place_add_key(GLFW_MOUSE_BUTTON_4, true);
	KeyPress place_sub_key(GLFW_MOUSE_BUTTON_5, true);
	win -> keys.push_back(&place_add_key);
	win -> keys.push_back(&place_sub_key);

	Point move;
	EntityBox entity(AxisBox(Point(-0.6, -3.2, -0.6), Point(+0.6, +0.2, +0.6)));

	std::cout << "loop\n";
	for (int i = 0; i < 20; i++)
		std::cout << "\n";
	while (!glfwWindowShouldClose(win -> win))
	{
		/*{
			std::stringstream ss;
			ss << "\e[18A\n";
			ss << "General Info\n";
			ss << "+-Memory:\n";
			ss << "  +-Static:\n";
			ss << "  | +-per Voxel:\n";
			ss << "  | | +-Memory: " << mem_size_1000_original(sizeof(Voxel)) << "\n";
			ss << "  | | +-Render: " << mem_size_1000_original(6 * 6 * sizeof(VoxelRenderData)) << "\n";
			ss << "  | +-per Chunks:\n";
			ss << "  |   +-Memory: " << mem_size_1000_original(Voxel_per_Chunk * sizeof(Voxel)) << "\n";
			ss << "  |   +-Render: " << mem_size_1000_original(Vertex_per_Chunk * 6 * 6 * sizeof(VoxelRenderData)) << "\n";
			ss << "  +-Dynamic:\n";
			ss << "    +-Space:\n";
			unsigned int count = space.GeneralInfoChunksCount();
			unsigned int mem_sum_data = space.GeneralInfoMemSumChunksData();
			unsigned int mem_sum_buff = space.GeneralInfoMemSumChunksBuff();
			ss << "      +-Chunks Count: " << count << "\n";
			ss << "      +-Chunks Memory Sum: " << mem_size_1000_original(mem_sum_data) << "\n";
			ss << "      +-Chunks Render Sum: " << mem_size_1000_original(mem_sum_buff) << "\n";
			if (count != 0)
			{
				ss << "      +-Chunks Memory Avg: " << mem_size_1000_original(mem_sum_data / count) << "\n";
				ss << "      +-Chunks Render Avg: " << mem_size_1000_original(mem_sum_buff / count) << "\n";
			}
			else
			{
				ss << "      +-Chunks Memory Avg: NaN\n";
				ss << "      +-Chunks Render Avg: NaN\n";
			}
			std::cout << ss.str();
		}*/

		win -> Update();

		FrameTimeCurr = glfwGetTime();
		FrameTimeDelta = FrameTimeCurr - FrameTimeLast;
		FrameTimeLast = FrameTimeCurr;
		//std::cout << "Delta: " << (FrameTimeDelta * 60) << "\n";


		move = view.RelToAbs(win -> GetKeyMovement(10.0f));
		//view.turn(win -> GetKeyTurning(0.03f));
		view.turn(win -> GetMouseTurning());

		if (test_Box_Key.check())
		{
			entity.pos = Point(0, 10, 0);
			entity.vel = Point();
		}
		entity.Update(space, FrameTimeDelta, move);
		view.pos = entity.pos;



		if (place_add_key.check())
		{
			placeID++;
			if (placeID >= (int)table.Length()) { placeID = 0; }
		}
		if (place_sub_key.check())
		{
			placeID--;
			if (placeID < 0) { placeID = table.Length() - 1; }
		}


		Index3D chunk_current;
		chunk_current.x = floorf(view.pos.x / Voxel_per_Side);
		chunk_current.y = floorf(view.pos.y / Voxel_per_Side);
		chunk_current.z = floorf(view.pos.z / Voxel_per_Side);

		space.AddChunksRange(chunk_current, 1);
		space.SubChunksRange(chunk_current, 2);

		VoxelHover hover;
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
		glActiveTexture(GL_TEXTURE_2D_ARRAY);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture_arr);
		space.Draw(Uni_Chunk_Pos);

		boxShader.Use();
		glUniform1f(Uni_Box_Cycle, FrameTimeCurr * 16);
		view.uniform(Uni_Box_View);
		view.uniform_depth(Uni_Box_Depth);
		space.DrawHover(hover);


		entity.DrawBox();


		Inv_Spin.x += FrameTimeDelta * 1;
		Inv_Spin.UpdateSinCos();
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE_2D_ARRAY);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture_arr);
		glBindVertexArray(Inv_Buffer_Array);
		inventoryShader.Use();
		glUniform2f(Uni_Inv_Pos, 0.75, 0.75);
		glUniform3fv(Uni_Inv_Spin, 2, (float *)&Inv_Spin);
		glUniform1ui(Uni_Inv_TexIdx, placeID);
		glDrawArrays(GL_TRIANGLES, 0, Inv_Render_Data_Count);


		glfwSwapBuffers(win -> win);
		glfwPollEvents();
	}

	glDeleteTextures(1, &texture_arr);
	delete win;

	glBindVertexArray(Inv_Buffer_Array);
	glDeleteBuffers(1, &Inv_Buffer_Vertex);
	glDeleteVertexArrays(1, &Inv_Buffer_Array);
	(void)Uni_Inv_Spin;
	(void)Uni_Inv_TexIdx;

	(void)Uni_Box_Cycle;
	(void)Uni_Box_View;
	(void)Uni_Box_Depth;

	return (0);
	(void)argc;
	(void)argv;
}
