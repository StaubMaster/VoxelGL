
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
#include "openGL/Forms/Inventory.hpp"
#include "openGL/Forms/HotBar.hpp"
#include "openGL/Forms/Debug.hpp"
#include "openGL/Forms/Controls/Text.hpp"

#include "openGL/Shader.hpp"
#include "openGL/View.hpp"

#include "./Grid/Chunk/VoxelChunk.hpp"
#include "./Grid/Space/VoxelSpace.hpp"

#include "AxisBox.hpp"
#include "EntityBox.hpp"

#include "FileParse/PNG/PNG_Image.hpp"

Window * win = NULL;

Shader * voxelShader = NULL;
int Uni_Voxel_View;
int Uni_Voxel_Depth;
int Uni_Voxel_Aspect;
int Uni_Voxel_ChunkPos;

Shader * boxShader = NULL;
int Uni_Box_View;
int Uni_Box_Depth;
int Uni_Box_Aspect;
int Uni_Box_Cycle;

Shader * textShader = NULL;
int Uni_Text_Size;

static void	main_init()
{
	win = new Window(1000, 1000, "Voxel", true);

	voxelShader = new Shader("Voxel",
		"shaders/voxel_project_tex.vert",
		"shaders/voxel_normal_tex.geom",
		"shaders/voxel_depth_tex.frag"
	);
	Uni_Voxel_View = voxelShader -> FindUniform("viewTrans");
	Uni_Voxel_Depth = voxelShader -> FindUniform("depthFactor");
	Uni_Voxel_Aspect = voxelShader -> FindUniform("aspectRatio");
	Uni_Voxel_ChunkPos = voxelShader -> FindUniform("chunk_pos");

	boxShader = new Shader("Box",
		"shaders/Box.vert",
		"shaders/Box.geom",
		"shaders/Cycle.frag"
	);
	Uni_Box_View = boxShader -> FindUniform("viewTrans");
	Uni_Box_Depth = boxShader -> FindUniform("depthFactor");
	Uni_Box_Aspect = boxShader -> FindUniform("aspectRatio");
	Uni_Box_Cycle = boxShader -> FindUniform("cycle");

	textShader = new Shader("Text",
		"shaders/Text.vert",
		"shaders/Text.frag"
	);
	Uni_Text_Size = textShader -> FindUniform("windowSize");

	ItemVoxel::Create();
	Form::CreateDraw();
}
static void	main_free()
{
	ItemVoxel::Delete();
	Form::DeleteDraw();

	delete voxelShader;
	delete boxShader;
	delete textShader;

	delete win;
}



double scrollX;
double scrollY;
void ScrollCallback(GLFWwindow *win, double x, double y)
{
	(void)win;
	scrollX = x;
	scrollY = y;
}



int main(int argc, char **argv)
{
	main_init();

{
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

	std::cout << "text ...\n";
	unsigned int text_texture;
	{
		glGenTextures(1, &text_texture);
		glBindTexture(GL_TEXTURE_2D, text_texture);

		//PNG_Image * text_img = PNG_Image::Load("images/fancy_Text15_16.png");
		PNG_Image * text_img = PNG_Image::Load("images/fancy_Text15_16_Thick.png");
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, text_img -> w, text_img -> h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, text_img -> data);
		delete text_img;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	BufferString text_Buff;
	text_Buff.Append(10, 10, 25.0f, "TestT\nline2");
	text_Buff.UpdateBuffer();
	std::cout << "text done\n";

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


	Point move;
	EntityBox entity(AxisBox(Point(-0.6, -3.2, -0.6), Point(+0.6, +0.2, +0.6)));
	entity.pos = Point(0, 10, 0);
	entity.vel = Point();



	KeyPress form_click(GLFW_MOUSE_BUTTON_1, true, false);
	win -> keys.push_back(&form_click);

	//KeyPress HotIncKey(GLFW_MOUSE_BUTTON_4, true);
	//KeyPress HotDecKey(GLFW_MOUSE_BUTTON_5, true);
	//win -> keys.push_back(&HotIncKey);
	//win -> keys.push_back(&HotDecKey);

	InventoryForm Inv(win -> Size, 12, 8);
	HotbarForm Hot(win -> Size, 12);
	DebugForm DBG(win -> Size);

	glfwSetScrollCallback(win -> win, ScrollCallback);

	for (unsigned int i = 0; i < table.Length(); i++)
		Inv.setSlot(i, i);
	int	cursorItemID = -1;



	double	FrameTimeLast = glfwGetTime();
	double	FrameTimeCurr;
	double	FrameTimeDelta;

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	std::cout << ">>>> loop\n";
	for (int i = 0; i < 20; i++)
		std::cout << "\n";
	while (!glfwWindowShouldClose(win -> win))
	{
		/*{
			std::stringstream ss;
			ss << "\e[17A\n";
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



		//if (HotIncKey.check())
		//	Hot.Inc();
		//if (HotDecKey.check())
		//	Hot.Dec();
		if (scrollY < 0) { Hot.Inc(); }
		if (scrollY > 0) { Hot.Dec(); }



		Index3D chunk_current;
		chunk_current.x = floorf(view.pos.x / Voxel_per_Side);
		chunk_current.y = floorf(view.pos.y / Voxel_per_Side);
		chunk_current.z = floorf(view.pos.z / Voxel_per_Side);

		space.AddChunksRange(chunk_current, 3);
		space.SubChunksRange(chunk_current, 6);
		space.UpdateChunks();


		VoxelHover hover;
		hover = space.Cross(view.pos, view.ang.rotate_back(Point(0, 0, 1)));
		if (voxel_add_key.check() && hover.isValid && Hot.SelectedItem() != -1)
			space.tryAdd(hover, Hot.SelectedItem());
		if (voxel_sub_key.check() && hover.isValid)
			space.trySub(hover, 0);



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1);



		voxelShader -> Use();
		view.uniform(Uni_Voxel_View);
		view.uniform_depth(Uni_Voxel_Depth);
		win -> UniformAspect(Uni_Voxel_Aspect);
		glActiveTexture(GL_TEXTURE_2D_ARRAY);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture_arr);
		space.Draw(Uni_Voxel_ChunkPos);

		boxShader -> Use();
		glUniform1f(Uni_Box_Cycle, FrameTimeCurr * 16);
		view.uniform(Uni_Box_View);
		view.uniform_depth(Uni_Box_Depth);
		win -> UniformAspect(Uni_Box_Aspect);
		space.DrawHover(hover);

		//entity.DrawBox();



		Point2D cursorPos = win -> CursorRasterized();
		//std::cout << cursorPos << "\n";

		if (form_click.check())
		{
			if (!DBG.Click())
			{
				Inv.Click(cursorItemID);
			}
		}
		Inv.Visible = !(win -> tabbed);
		DBG.Visible = !(win -> tabbed);

		Inv.UpdateAnchor(win -> Size);
		Hot.UpdateAnchor(win -> Size);
		DBG.UpdateAnchor(win -> Size);

		Hot.Syncronize(Inv);
		Inv.UpdateHover(cursorPos);
		DBG.UpdateHover(cursorPos);

		ItemVoxel::Update(FrameTimeDelta);
		win -> UniformAspect(ItemVoxel::UniformAspect());
		win -> UniformSize(ItemVoxel::UniformSize());
		win -> UniformAspect(Form::UniformAspect());
		win -> UniformSize(Form::UniformSize());
		glActiveTexture(GL_TEXTURE_2D_ARRAY);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture_arr);

		Hot.Draw();
		Inv.Draw();
		if (cursorItemID != -1) { ItemVoxel::Draw(cursorPos.X, cursorPos.Y, cursorItemID); }
		DBG.Draw();


		{
			textShader -> Use();
			win -> UniformSize(Uni_Text_Size);

			glClear(GL_DEPTH_BUFFER_BIT);
			glActiveTexture(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, text_texture);

			DBG.DrawText();
			text_Buff.Draw();
		}

		scrollX = 0;
		scrollY = 0;

		glfwSwapBuffers(win -> win);
		glfwPollEvents();
	}
	std::cout << "<<<< loop\n";

	glDeleteTextures(1, &text_texture);
	glDeleteTextures(1, &texture_arr);
}

	main_free();

	return (0);
	(void)argc;
	(void)argv;
}
