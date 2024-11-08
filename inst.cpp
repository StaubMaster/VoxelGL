
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "openGL/openGL.h"

typedef struct s_inst_trans
{
	float pos_x, pos_y, pos_z;
	float sin_x, sin_y, sin_z;
	float cos_x, cos_y, cos_z;
	float ang_x, ang_y, ang_z;
}	t_inst_trans;
void inst_sin_cos(t_inst_trans *inst)
{
	inst -> sin_x = sin(inst -> ang_x);
	inst -> sin_y = sin(inst -> ang_y);
	inst -> sin_z = sin(inst -> ang_z);
	inst -> cos_x = cos(inst -> ang_x);
	inst -> cos_y = cos(inst -> ang_y);
	inst -> cos_z = cos(inst -> ang_z);
}

static int	Prog_ID;
static int	Uni_View;

static unsigned int	Buffer_Array;
static unsigned int	Buffer_Corn;
static unsigned int	Buffer_Index;
static unsigned int	Buffer_Inst;

static int IndexCount;
static int InstCount;

static unsigned int Texture1;

void	inst_delete()
{
	if (Buffer_Array != 0xFFFFFFFF)
	{
		glBindVertexArray(Buffer_Array);
		if (Buffer_Corn != 0xFFFFFFFF)
		{
			glDeleteBuffers(1, &Buffer_Corn);
			Buffer_Corn = 0xFFFFFFFF;
		}
		if (Buffer_Index != 0xFFFFFFFF)
		{
			glDeleteBuffers(1, &Buffer_Index);
			Buffer_Index = 0xFFFFFFFF;
		}
		if (Buffer_Inst != 0xFFFFFFFF)
		{
			glDeleteBuffers(1, &Buffer_Inst);
			Buffer_Inst = 0xFFFFFFFF;
		}
		glDeleteVertexArrays(1, &Buffer_Array);
		Buffer_Array = 0xFFFFFFFF;
	}

	if (Prog_ID != -1)
	{
		Uni_View = -1;
		glDeleteProgram(Prog_ID);
		Prog_ID = -1;
	}

	if (Texture1 != 0xFFFFFFFF)
	{
		glDeleteTextures(1, &Texture1);
		Texture1 = 0xFFFFFFFF;
	}
}

void	inst_init()
{
	Prog_ID = -1;
	Uni_View = -1;
	Buffer_Array = 0xFFFFFFFF;
	Buffer_Corn = 0xFFFFFFFF;
	Buffer_Index = 0xFFFFFFFF;
	Buffer_Inst = 0xFFFFFFFF;
	Texture1 = 0xFFFFFFFF;
}

int		inst_load_program()
{
	Prog_ID = load_programVGF(
		"shaders/inst_project.vert",
		"shaders/faceNormal.geom",
		"shaders/dirLight.frag");
	if (Prog_ID == -1)
		return (0);
	Uni_View = glGetUniformLocation(Prog_ID, "view");
	return (1);
}




void	inst_buffer_gen()
{
	glGenVertexArrays(1, &Buffer_Array);
	glGenBuffers(1, &Buffer_Corn);
	glGenBuffers(1, &Buffer_Index);
	glGenBuffers(1, &Buffer_Inst);
}

void	inst_buffer_data_corn(float *data, int count)
{
	glUseProgram(Prog_ID);
	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_Corn);

	glBufferData(GL_ARRAY_BUFFER, count * 5 * sizeof(float), data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
}

void	inst_buffer_data_index(unsigned int *data, int count)
{
	glUseProgram(Prog_ID);
	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffer_Index);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
	IndexCount = count;
}

void	inst_buffer_data_inst(t_inst_trans *data, int count)
{
	glUseProgram(Prog_ID);
	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_Inst);

	glBufferData(GL_ARRAY_BUFFER, count * 12 * sizeof(float), data, GL_STREAM_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)(0 * sizeof(float)));
	glVertexAttribDivisor(2, 1);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)(3 * sizeof(float)));
	glVertexAttribDivisor(3, 1);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)(6 * sizeof(float)));
	glVertexAttribDivisor(4, 1);

	InstCount = count;
}



void	inst_texture_gen()
{
	glGenTextures(1, &Texture1);
	glBindTexture(GL_TEXTURE_2D, Texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

int	inst_texture_load(const char *name)
{
	int w, h;
	unsigned int *texData;
	texture_load(name, &texData, &w, &h);
	if (texData == NULL)
		return (0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, texData);
	free(texData);
	glGenerateMipmap(GL_TEXTURE_2D);
	return (1);
}



void	inst_view(t_view *view)
{
	glUseProgram(Prog_ID);
	glUniform3fv(Uni_View, 3, (view -> data));
}

void	inst_draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture1);

	glUseProgram(Prog_ID);
	glBindVertexArray(Buffer_Array);
	glDrawElementsInstanced(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, (void*)0, InstCount);
}


