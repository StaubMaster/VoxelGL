
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
#include "openGL/Forms/FormControl.hpp"
#include "openGL/Forms/ItemVoxel.hpp"
#include "openGL/Shader.hpp"
#include "openGL/View.hpp"

#include "Voxel/VoxelChunk.hpp"
#include "Voxel/VoxelSpace.hpp"

#include "AxisBox.hpp"
#include "EntityBox.hpp"

#include "FileParse/PNG/PNG_Image.hpp"

Window * win = NULL;

Shader * voxelShader = NULL;
int Uni_Voxel_View;
int Uni_Voxel_Depth;
int Uni_Voxel_ChunkPos;

Shader * boxShader = NULL;
int Uni_Box_View;
int Uni_Box_Depth;
int Uni_Box_Cycle;


static void	main_init()
{
	std::cout << "window ...\n";
	win = new Window(1000, 1000, "Voxel", false);
	std::cout << "window done\n";



	std::cout << "shaders ...\n";

	voxelShader = new Shader(
		"shaders/voxel_project_tex.vert",
		"shaders/voxel_normal_tex.geom",
		"shaders/voxel_depth_tex.frag"
	);
	Uni_Voxel_View = voxelShader -> FindUniform("viewTrans");
	Uni_Voxel_Depth = voxelShader -> FindUniform("depthFactor");
	Uni_Voxel_ChunkPos = voxelShader -> FindUniform("chunk_pos");

	boxShader = new Shader(
		"shaders/Box.vert",
		"shaders/Box.geom",
		"shaders/Cycle.frag"
	);
	Uni_Box_View = boxShader -> FindUniform("viewTrans");
	Uni_Box_Depth = boxShader -> FindUniform("depthFactor");
	Uni_Box_Cycle = boxShader -> FindUniform("cycle");

	std::cout << "shaders done\n";


	ItemVoxel::Create();
}
static void	main_free()
{
	ItemVoxel::Delete();

	delete voxelShader;
	delete boxShader;

	delete win;
}



int main(int argc, char **argv)
{
	main_init();

	std::cout << "table ...\n";
	VoxelDataTable table;
	table.Set(VoxelData("images/TextureAlign.png",     false, false, false, true , false));
	table.Set(VoxelData("images/fancy_GreenDirt.png",  false, false, false, false, false));
	table.Set(VoxelData("images/fancy_RedWood.png",    false, false, false, true , false));
	table.Set(VoxelData("images/fancy_BlueSpiral.png", false, false, true , false, false));
	table.Set(VoxelData("images/BlueSpiral.png",       false, false, false, false, false));
	table.Set(VoxelData("images/Brick.png",            false, false, false, true , false));
	table.Set(VoxelData("images/Window.png",           false, false, true , false, false));
	table.Set(VoxelData("images/RedPlank.png",         false, false, false, true , true ));
	table.Set(VoxelData("images/WoodPlank.png",        false, false, false, true , true ));
	std::cout << "table done\n";

	std::cout << "textures ...\n";
	unsigned int texture_arr = table.InitTextures();
	std::cout << "textures done\n";


	View view;
	VoxelSpace space(table);


	KeyPress test_Box_Key(GLFW_KEY_Q, false);
	win -> keys.push_back(&test_Box_Key);

	KeyPress voxel_add_key(GLFW_MOUSE_BUTTON_1, true);
	KeyPress voxel_sub_key(GLFW_MOUSE_BUTTON_2, true);
	win -> keys.push_back(&voxel_add_key);
	win -> keys.push_back(&voxel_sub_key);

	char	placeID = 0;
	KeyPress place_add_key(GLFW_MOUSE_BUTTON_4, true);
	KeyPress place_sub_key(GLFW_MOUSE_BUTTON_5, true);
	win -> keys.push_back(&place_add_key);
	win -> keys.push_back(&place_sub_key);


	Point move;
	EntityBox entity(AxisBox(Point(-0.6, -3.2, -0.6), Point(+0.6, +0.2, +0.6)));


	FormControlList formList;
	FormControl form1(-0.50f, -0.25f, +0.50f, +0.25f);
	FormButton button1(-0.45f, -0.20f, -0.15f, -0.10f);
	FormButton button2(-0.10f, -0.20f, +0.20f, -0.10f);

	float x = -0.6f;
	float y = +0.3f - 0.2f;
	int slots_count = 6;
	FormSlot slots[]
	{
		FormSlot(x + 0 * 0.2f, y, x + 1 * 0.2f, y + 0.2f),
		FormSlot(x + 1 * 0.2f, y, x + 2 * 0.2f, y + 0.2f),
		FormSlot(x + 2 * 0.2f, y, x + 3 * 0.2f, y + 0.2f),
		FormSlot(x + 3 * 0.2f, y, x + 4 * 0.2f, y + 0.2f),
		FormSlot(x + 4 * 0.2f, y, x + 5 * 0.2f, y + 0.2f),
		FormSlot(x + 5 * 0.2f, y, x + 6 * 0.2f, y + 0.2f),
	};
	formList.Insert(form1);
	formList.Insert(button1);
	formList.Insert(button2);
	for (int i = 0; i < slots_count; i++)
		formList.Insert(slots[i]);
	formList.UpdateBuffer();

	int	mouse_itemID = 0;
	mouse_itemID = 0; slots[0].SwapItem(mouse_itemID);
	mouse_itemID = 1; slots[1].SwapItem(mouse_itemID);
	mouse_itemID = 2; slots[2].SwapItem(mouse_itemID);


	double	FrameTimeLast = glfwGetTime();
	double	FrameTimeCurr;
	double	FrameTimeDelta;

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

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


		voxelShader -> Use();
		view.uniform(Uni_Voxel_View);
		view.uniform_depth(Uni_Voxel_Depth);
		glActiveTexture(GL_TEXTURE_2D_ARRAY);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture_arr);
		space.Draw(Uni_Voxel_ChunkPos);

		boxShader -> Use();
		glUniform1f(Uni_Box_Cycle, FrameTimeCurr * 16);
		view.uniform(Uni_Box_View);
		view.uniform_depth(Uni_Box_Depth);
		space.DrawHover(hover);

		entity.DrawBox();



		Point2D mouse;
		{
			double	mouse_x_dbl;
			double	mouse_y_dbl;
			glfwGetCursorPos(win -> win, &mouse_x_dbl, &mouse_y_dbl);
			mouse.X = (mouse_x_dbl / 500) - 1;
			mouse.Y = 1 - (mouse_y_dbl / 500);
		}

		if (voxel_add_key.check())
		{
			for (int i = 0; i < slots_count; i++)
			{
				if (slots[i].isHover(mouse))
				{
					slots[i].SwapItem(mouse_itemID);
					break;
				}
			}
		}

		formList.Update(win);
		formList.Draw();

		glActiveTexture(GL_TEXTURE_2D_ARRAY);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture_arr);
		ItemVoxel::Update(FrameTimeDelta);
		if (mouse_itemID != -1)
			ItemVoxel::Draw(mouse.X, mouse.Y, mouse_itemID);
		for (int i = 0; i < slots_count; i++)
			slots[i].DrawItem();



		glfwSwapBuffers(win -> win);
		glfwPollEvents();
	}

	main_free();

	glDeleteTextures(1, &texture_arr);

	return (0);
	(void)argc;
	(void)argv;
}
