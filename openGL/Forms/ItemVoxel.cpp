
#include "ItemVoxel.hpp"

static Angle	Spin = Angle(1, 0.5, 0);

static Shader *	shader = NULL;
static int Uni_Spin;
static int Uni_Pos;
static int Uni_TexIdx;

static unsigned int	Buffer_Array = 9;
static unsigned int	Buffer_Main = 9;
static unsigned int Data_Count = 9;

void ItemVoxel::Create()
{
	shader = new Shader(
		"shaders/inventory.vert",
		"shaders/inventory.geom",
		"shaders/inventory.frag"
	);
	Uni_Pos = shader -> FindUniform("UPos");
	Uni_Spin = shader -> FindUniform("USpin");
	Uni_TexIdx = shader -> FindUniform("UTex_Idx");

	glGenVertexArrays(1, &Buffer_Array);
	glBindVertexArray(Buffer_Array);
	glGenBuffers(1, &Buffer_Main);

	Data_Count = 36;
	float Render_Data[] =
	{
		-1.0f, -1.0f, -1.0f, 0.25f, 1.0f,
		-1.0f, -1.0f, +1.0f, 0.25f, 0.5f,
		-1.0f, +1.0f, -1.0f, 0.00f, 1.0f,
		-1.0f, +1.0f, -1.0f, 0.00f, 1.0f,
		-1.0f, -1.0f, +1.0f, 0.25f, 0.5f,
		-1.0f, +1.0f, +1.0f, 0.00f, 0.5f,

		-1.0f, -1.0f, -1.0f, 0.50f, 1.0f,
		+1.0f, -1.0f, -1.0f, 0.50f, 0.5f,
		-1.0f, -1.0f, +1.0f, 0.25f, 1.0f,
		-1.0f, -1.0f, +1.0f, 0.25f, 1.0f,
		+1.0f, -1.0f, -1.0f, 0.50f, 0.5f,
		+1.0f, -1.0f, +1.0f, 0.25f, 0.5f,

		-1.0f, -1.0f, -1.0f, 0.75f, 1.0f,
		-1.0f, +1.0f, -1.0f, 0.75f, 0.5f,
		+1.0f, -1.0f, -1.0f, 0.50f, 1.0f,
		+1.0f, -1.0f, -1.0f, 0.50f, 1.0f,
		-1.0f, +1.0f, -1.0f, 0.75f, 0.5f,
		+1.0f, +1.0f, -1.0f, 0.50f, 0.5f,

		+1.0f, -1.0f, -1.0f, 0.25f, 0.5f,
		+1.0f, +1.0f, -1.0f, 0.00f, 0.5f,
		+1.0f, -1.0f, +1.0f, 0.25f, 0.0f,
		+1.0f, -1.0f, +1.0f, 0.25f, 0.0f,
		+1.0f, +1.0f, -1.0f, 0.00f, 0.5f,
		+1.0f, +1.0f, +1.0f, 0.00f, 0.0f,

		-1.0f, +1.0f, -1.0f, 0.50f, 0.5f,
		-1.0f, +1.0f, +1.0f, 0.25f, 0.5f,
		+1.0f, +1.0f, -1.0f, 0.50f, 0.0f,
		+1.0f, +1.0f, -1.0f, 0.50f, 0.0f,
		-1.0f, +1.0f, +1.0f, 0.25f, 0.5f,
		+1.0f, +1.0f, +1.0f, 0.25f, 0.0f,

		-1.0f, -1.0f, +1.0f, 0.75f, 0.5f,
		+1.0f, -1.0f, +1.0f, 0.50f, 0.5f,
		-1.0f, +1.0f, +1.0f, 0.75f, 0.0f,
		-1.0f, +1.0f, +1.0f, 0.75f, 0.0f,
		+1.0f, -1.0f, +1.0f, 0.50f, 0.5f,
		+1.0f, +1.0f, +1.0f, 0.50f, 0.0f,
	};
	for (unsigned int i = 0; i < Data_Count * 5; i += 5)
	{
		Render_Data[i + 0] *= 0.05f;
		Render_Data[i + 1] *= 0.05f;
		Render_Data[i + 2] *= 0.05f;
	}

	glBindBuffer(GL_ARRAY_BUFFER, Buffer_Main);
	glBufferData(GL_ARRAY_BUFFER, Data_Count * sizeof(float) * 5, Render_Data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, (void *)(sizeof(float) * 3));
}

void ItemVoxel::Delete()
{
	delete shader;

	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Main);
	glDeleteVertexArrays(1, &Buffer_Array);
}



void ItemVoxel::Update(float time)
{
	Spin.x += time * 1;
	Spin.UpdateSinCos();
}



void ItemVoxel::Draw(float x, float y, int idx)
{
	shader -> Use();

	glUniform3fv(Uni_Spin, 2, (float *)&Spin);
	glUniform2f(Uni_Pos, x, y);
	glUniform1ui(Uni_TexIdx, idx);

	glClear(GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(Buffer_Array);
	glDrawArrays(GL_TRIANGLES, 0, Data_Count);
}
