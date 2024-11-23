
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




Point	Box::IntersektSize(Box & other)
{
/*
	Box with '+' : this
	Box with '#' : other

			|	|	X Diff
			|	|
	+-----------+
	|			|
	|			|
	|		#-------#----
	|		|	|	|	Y Diff
	+-------|---+	|----
			|		|
			#-------#

other fully inside this :
	+-----------+
	|			|
	|	#---#	|
	|	|	|	|	no X Intersekt
	+---|---|---+
		|	|
		#---#

this fully inside other:
		+---+
		|	|
	#---|---|---#
	|	|	|	|	no X Intersekt
	|	+---+	|
	|			|
	#-----------#

no intersection:
	+---+	#---#
	|	|	|	|	no X Intersekt
	+---+	#---#
*/

/*
	1	2	3	4

	|		|
	|	#---|---#
	|	|	|	|
	+---|---+	|
		|		|

	min_intersekt = 2 - 1 = +1
	max_intersekt = 4 - 3 = +1

	min_intersekt > 0 : no overlap
	max_intersekt > 0 : overlap

	1	2	3	4

	|	|
	|	|	#---#
	|	|	|	|
	+---+	|	|
			|	|

	min_intersekt = 3 - 1 = +2
	max_intersekt = 4 - 2 = +2
*/

	Point	diff;
	double	min_intersekt;
	double	max_intersekt;

	if (Min.x < other.Max.x && other.Min.x < Max.x)
	{
		min_intersekt = other.Min.x - Min.x;
		max_intersekt = other.Max.x - Max.x;
		if (min_intersekt < 0 && max_intersekt < 0)
			diff.x = min_intersekt;
		if (min_intersekt > 0 && max_intersekt > 0)
		diff.x = max_intersekt;
	}

	if (Min.y < other.Max.y && other.Min.y < Max.y)
	{
		min_intersekt = other.Min.y - Min.y;
		max_intersekt = other.Max.y - Max.y;
		if (min_intersekt < 0 && max_intersekt < 0)
			diff.y = min_intersekt;
		if (min_intersekt > 0 && max_intersekt > 0)
			diff.y = max_intersekt;
	}

	if (Min.z < other.Max.z && other.Min.z < Max.z)
	{
		min_intersekt = other.Min.z - Min.z;
		max_intersekt = other.Max.z - Max.z;
		if (min_intersekt < 0 && max_intersekt < 0)
			diff.z = min_intersekt;
		if (min_intersekt > 0 && max_intersekt > 0)
			diff.z = max_intersekt;
	}

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
