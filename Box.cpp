
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



bool	Box::IntersektBool(const Box & b1, const Box & b2)
{
	return (
		b1.Min.x < b2.Max.x && b1.Max.x > b2.Min.x &&
		b1.Min.y < b2.Max.y && b1.Max.y > b2.Min.y &&
		b1.Min.z < b2.Max.z && b1.Max.z > b2.Min.z);
}

/*
	used for pushing 2 boxes apart
	b1 should be the static box
	b2 should be the box that moves
*/
Point	Box::IntersektDiff(const Box & b1, const Box & b2)
{
	Point	diff;
	Point	diff_min = b2.Min - b1.Min;
	Point	diff_max = b2.Max - b1.Max;

	if (!IntersektBool(b1, b2))
	{
		return Point();
	}

	if (diff_min.x < 0 && diff_max.x < 0)
		diff.x = diff_min.x;
	if (diff_min.x > 0 && diff_max.x > 0)
	diff.x = diff_max.x;

	if (diff_min.y < 0 && diff_max.y < 0)
		diff.y = diff_min.y;
	if (diff_min.y > 0 && diff_max.y > 0)
		diff.y = diff_max.y;

	if (diff_min.z < 0 && diff_max.z < 0)
		diff.z = diff_min.z;
	if (diff_min.z > 0 && diff_max.z > 0)
		diff.z = diff_max.z;

	return diff;
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
