
#include "Box.hpp"

Box::Box()
{
	Buffer_Array = 0xFFFFFFFF;
	Buffer_MinMax = 0xFFFFFFFF;
}
Box::Box(Point a, Point b) :
	Min(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)),
	Max(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z))
{
	Buffer_Array = 0xFFFFFFFF;
	Buffer_MinMax = 0xFFFFFFFF;
}
Box::~Box()
{
	if (Buffer_Array != 0xFFFFFFFF)
	{
		glBindVertexArray(Buffer_Array);
		if (Buffer_MinMax != 0xFFFFFFFF)
		{
			glDeleteBuffers(1, &Buffer_MinMax);
		}
		glDeleteVertexArrays(1, &Buffer_Array);
	}
}

void	Box::CreateBuffer()
{
	if (Buffer_Array == 0xFFFFFFFF)
	{
		glGenVertexArrays(1, &Buffer_Array);
		glGenBuffers(1, &Buffer_MinMax);
	}
}
void	Box::UpdateBuffer()
{
	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_MinMax);

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(unsigned int), (float *)this, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(0, 3, GL_UNSIGNED_INT, 6 * sizeof(unsigned int), (void *)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribIPointer(1, 3, GL_UNSIGNED_INT, 6 * sizeof(unsigned int), (void *)(3 * sizeof(float)));
}
void	Box::Draw()
{
	glBindVertexArray(Buffer_Array);
	glDrawArrays(GL_POINTS, 0, 1);
}
