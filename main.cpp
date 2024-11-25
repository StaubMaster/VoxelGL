
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
	std::cout << "table done\n";

	std::cout << "textures ...\n";
	unsigned int texture_arr = table.InitTextures();
	std::cout << "textures done\n";

	View view;
	//view.pos.z = -(128 + 10);
	VoxelSpace space(table);


	KeyPress test_Box_Key(GLFW_KEY_Q, false);
	win -> keys.push_back(&test_Box_Key);

	Box box1(Point(-1, 3, -1), Point(1, 4, 1));
	Box box2(Point(-0.5, 4.5, -0.5), Point(0.5, 5, 0.5));
	Box box3;
	box1.CreateBuffer();
	box1.UpdateBuffer();
	box2.CreateBuffer();
	box2.UpdateBuffer();
	box3.CreateBuffer();



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

	{
		std::cout << "General Info\n";
		std::cout << "  Memory:\n";
		std::cout << "    per Chunks:\n";
		std::cout << "      Voxels: " << mem_size_1000_original(Voxel_per_Chunk * sizeof(Voxel)) << "\n";
		std::cout << "      Buffer: " << mem_size_1000_original(Vertex_per_Chunk * 6 * 6 * sizeof(VoxelRenderData)) << "\n";
	}

	Point vel;

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
		glActiveTexture(GL_TEXTURE_2D_ARRAY);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture_arr);
		space.Draw(Uni_Chunk_Pos);

		boxShader.Use();
		glUniform1f(Uni_Box_Cycle, FrameTimeCurr * 16);
		view.uniform(Uni_Box_View);
		view.uniform_depth(Uni_Box_Depth);
		space.DrawHover(hover);

/*
	+---------------+
	| +-----------+ |
	| | +-------+ | |
	| | |       | | |
	| | |       | | |
	| | +-------+ | |
	| +-----------+ |
	+---------------+

	outer : determin on what sides surfaces are being touched
	middle : collision target
	inner : determin if stuch

	if outer collides with voxel on bottom
		on ground, no gravity

	if inner collides with voxel at all
		stuck, no gravity, (push to unstuck ?)

	for movement
		check how far middle can move until collide
		move middle

problem: moving diagonal
	should slide off surface
solution:
	use outer to degermin which if touching surface
	when touching surface, dont move calcle all movement toward that surface

*/

		if (test_Box_Key.check())
		{
			//view.pos = view.pos + vel;
			//box2.Min = Point(0, 3.5, 0);
			//box2.Max = Point(1.5, 5.0, 1.5);
			box2.Min = view.pos + Point(-0.3, -1.0, -0.3);
			box2.Max = view.pos + Point(+0.3, +0.3, +0.3);
			//vel = Point();
			//vel.y = 0.001f;
		}

		{
			box2.Min = box2.Min + vel;
			box2.Max = box2.Max + vel;

			vel = vel * 0.9999f;
			vel.y -= 0.0001f;
			//Point diff = Box::IntersektDiff(box1, box2);
			//Point diff = space.CheckBoxCollision(box2);
			//diff = diff.Sign();

			box3.Min = box2.Min - Point(0.1f, 0.1f, 0.1f);
			box3.Max = box2.Max + Point(0.1f, 0.1f, 0.1f);

			Point diff = space.IntersektDiff(box3);
			std::cout << "diff " << diff << "\n";
			std::cout << "vel " << vel << "\n";

			if (abs(diff.x) >= 0.1f)
				vel.x = 0;
			else if (abs(diff.x) > 0)
			{
				std::cout << "X\n";
				vel.x += diff.x;
			}
			if (abs(diff.y) >= 0.1f)
				vel.y = 0;
			else if (abs(diff.y) > 0)
			{
				if (diff.y < 0 && vel.y > 0)
				{
					std::cout << "Y--\n";
					vel.y += diff.y;
					if (vel.y < 0)
						vel.y = 0;
				}
				else if (diff.y > 0 && vel.y < 0)
				{
					std::cout << "Y++\n";
					vel.y += diff.y;
					if (vel.y > 0)
						vel.y = 0;
				}
			}
			if (abs(diff.z) >= 0.1f)
				vel.z = 0;
			else if (abs(diff.z) > 0)
			{
				std::cout << "Z\n";
				vel.z += diff.z;
			}

			//float t = space.CheckBoxCollision(box2, vel);
			//std::cout << "t: " << t << "\n";
			//if (t > 0 && t < 1)
			//{
			//	vel = vel * (t - 0.001f);
			//}
			//if (!space.IntersektBool(box3))
			//{
			//	std::cout << "not on ground\n";
			//	vel.y -= 0.0001f;
			//}

			//diff.y -= 0.01f;
			//diff = diff * 0.001f;
			//vel = vel + diff;

			if (vel.length() > 0.5f)
				vel = vel * (0.5 / vel.length());

			box2.UpdateBuffer();
			box3.UpdateBuffer();
		}

		box1.Draw();
		box2.Draw();
		box3.Draw();



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
