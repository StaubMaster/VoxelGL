
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "openGL/openGL.h"


void	f_rot(float *pls, float *mns, float cos, float sin)
{
	float	temppp;

	temppp = pls[0] * cos - mns[0] * sin;
	mns[0] = mns[0] * cos + pls[0] * sin;
	pls[0] = temppp;
}

void leaks(void)
{
	system("leaks test");
}

int main(void)
{
	//atexit(leaks);

	GLFWwindow	*win;
	win = load_window(1000, 1000, "test");
	if (win == NULL)
	{
		exit(EXIT_FAILURE);
	}

	int Prog_ID;
	Prog_ID = load_programVF("shaders/simple.vert", "shaders/simple.frag");
	if (Prog_ID == -1)
	{
		glfwDestroyWindow(win);
		exit(EXIT_FAILURE);
	}

	unsigned int Buffer_Array;
	unsigned int Buffer_PosCol;
	glGenVertexArrays(1, &Buffer_Array);
	glGenBuffers(1, &Buffer_PosCol);



	glUseProgram(Prog_ID);
	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_PosCol);


	float PosCol[] = (float[])
	{
		-0.6f, -0.6f, 1.0f, 0.0f, 0.0f,
		+0.6f, -0.6f, 0.0f, 1.0f, 0.0f,
		-0.6f, +0.6f, 0.0f, 0.0f, 1.0f,
	};


	float wnk_sin, wnk_cos;
	wnk_sin = sin(0.05);
	wnk_cos = cos(0.05);
	while (!glfwWindowShouldClose(win))
	{
		if (glfwGetKey(win, GLFW_KEY_ESCAPE)) { glfwSetWindowShouldClose(win, 1); }

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(float), PosCol, GL_STREAM_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(0 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(win);
		glfwPollEvents();

		f_rot(&PosCol[0x0], &PosCol[0x1], wnk_cos, wnk_sin);
		f_rot(&PosCol[0x5], &PosCol[0x6], wnk_cos, wnk_sin);
		f_rot(&PosCol[0xA], &PosCol[0xB], wnk_cos, wnk_sin);
	}
	glfwDestroyWindow(win);

	glDeleteProgram(Prog_ID);

	glDeleteBuffers(1, &Buffer_PosCol);
	glDeleteVertexArrays(1, &Buffer_Array);

	return (0);
}
