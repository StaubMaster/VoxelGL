
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

Box::Box(const Box & other)
{
	Min = other.Min;
	Max = other.Max;
	Buffer_Array = 0xFFFFFFFF;
	Buffer_MinMax = 0xFFFFFFFF;
}
const Box & Box::operator =(const Box & other)
{
	Min = other.Min;
	Max = other.Max;
	Buffer_Array = 0xFFFFFFFF;
	Buffer_MinMax = 0xFFFFFFFF;
	return *this;
}





Box	Box::Move(Point rel) const
{
	return Box(Min + rel, Max + rel);
}



bool	Box::IntersektBoolX(const Box & b1, const Box & b2)
{
	return (b1.Min.x < b2.Max.x && b1.Max.x > b2.Min.x);
}
bool	Box::IntersektBoolY(const Box & b1, const Box & b2)
{
	return (b1.Min.y < b2.Max.y && b1.Max.y > b2.Min.y);
}
bool	Box::IntersektBoolZ(const Box & b1, const Box & b2)
{
	return (b1.Min.z < b2.Max.z && b1.Max.z > b2.Min.z);
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
/*
	1	2	3	4

	|	b1	|

		|	b2	|

		|---|		diff_min = b1.max - b2.min
	|-----------|	diff_max = b2.max - b1.min
					diff = diff_max - diff_min

	diff_min = 3 - 2 = +1
	diff_max = 4 - 1 = +3
	diff = 3 - 1 = +2

	1	2	3	4

		|	b1	|

	|	b2	|

	|-----------|	diff_min = b1.max - b2.min
		|---|		diff_max = b2.max - b1.min
					diff = diff_max - diff_min

	diff_min = 4 - 1 = +3
	diff_max = 3 - 2 = +1
	diff = 1 - 3 = -2
*/

/*
	1	2	3	4	5	6
	|-----------|
			|-----------|
	should return +1

	1	2	3	4	5	6
	|-----------|
		|-----------|
	should return +2

	1	2	3	4	5	6
	|-----------|
	|-----------|
	should return +-3

	1	2	3	4	5	6
		|-----------|
	|-----------|
	should return -2

	1	2	3	4	5	6
			|-----------|
	|-----------|
	should return -3

	3 - 4 = -1	:	1.min - 2.max
	6 - 1 = +5	:	1.max - 2.min
	abs(-1) < abs(+5) : return (-1)

	1 - 6 = -5
	4 - 3 = +1
	abs(+1) < abs(-5) : return (+1)
*/
Point	Box::IntersektDiff(const Box & b1, const Box & b2)
{
	if (!IntersektBool(b1, b2))
	{
		return Point();
	}

	//Point	diff;
	//Point	diff_min = b2.Min - b1.Min;
	//Point	diff_max = b2.Max - b1.Max;

	Point	diff_min = b1.Min - b2.Max;
	Point	diff_max = b1.Max - b2.Min;
	Point	diff;

	if (abs(diff_min.x) < abs(diff_max.x))
		diff.x = diff_min.x;
	if (abs(diff_min.x) > abs(diff_max.x))
		diff.x = diff_max.x;

	if (abs(diff_min.y) < abs(diff_max.y))
		diff.y = diff_min.y;
	if (abs(diff_min.y) > abs(diff_max.y))
		diff.y = diff_max.y;

	if (abs(diff_min.z) < abs(diff_max.z))
		diff.z = diff_min.z;
	if (abs(diff_min.z) > abs(diff_max.z))
		diff.z = diff_max.z;

	return (diff);

	//if (diff_min.x < 0 && diff_max.x < 0)
	//	diff.x = diff_min.x;
	//if (diff_min.x > 0 && diff_max.x > 0)
	//	diff.x = diff_max.x;

	//if (diff_min.y < 0 && diff_max.y < 0)
	//	diff.y = diff_min.y;
	//if (diff_min.y > 0 && diff_max.y > 0)
	//	diff.y = diff_max.y;

	//if (diff_min.z < 0 && diff_max.z < 0)
	//	diff.z = diff_min.z;
	//if (diff_min.z > 0 && diff_max.z > 0)
	//	diff.z = diff_max.z;

	//return diff;
}

/*
	find out how far box2 needs to move along v2 to touch box1
	if never : return NAN

	t is expected to be above 0
	if no t above 0 is found : return NAN
*/
/*
	-------- b2.max.y
	 \
	  \ v2.y
	   \
	-------- b1.min.y

	b1.min.y = b2.max.y + v2.y * t
	t = (b1.min.y - b2.max.y) / v2.y

	check if at t the other 2 coord intersekt
*/
double	Box::IntersektT(const Box & b1, const Box & b2, const Point v2)
{
	float	t = FP_INFINITE;
	float	t_temp;
	Box	b2_at_t;

	if (v2.x != 0)
	{
		t_temp = (b1.Min.x - b2.Max.x) / v2.x;
		if (t_temp > 0 && t_temp < t)
		{
			b2_at_t = b2.Move(v2 * t_temp);
			if (IntersektBoolY(b1, b2_at_t) && IntersektBoolZ(b1, b2_at_t))
				t = t_temp;
		}
		t_temp = (b1.Max.x - b2.Min.x) / v2.x;
		if (t_temp > 0 && t_temp < t)
		{
			b2_at_t = b2.Move(v2 * t_temp);
			if (IntersektBoolY(b1, b2_at_t) && IntersektBoolZ(b1, b2_at_t))
				t = t_temp;
		}
	}

	if (v2.y != 0)
	{
		t_temp = (b1.Min.y - b2.Max.y) / v2.y;
		if (t_temp > 0 && t_temp < t)
		{
			b2_at_t = b2.Move(v2 * t_temp);
			if (IntersektBoolZ(b1, b2_at_t) && IntersektBoolX(b1, b2_at_t))
				t = t_temp;
		}
		t_temp = (b1.Max.y - b2.Min.y) / v2.y;
		if (t_temp > 0 && t_temp < t)
		{
			b2_at_t = b2.Move(v2 * t_temp);
			if (IntersektBoolZ(b1, b2_at_t) && IntersektBoolX(b1, b2_at_t))
				t = t_temp;
		}
	}

	if (v2.z != 0)
	{
		t_temp = (b1.Min.z - b2.Max.z) / v2.z;
		if (t_temp > 0 && t_temp < t)
		{
			b2_at_t = b2.Move(v2 * t_temp);
			if (IntersektBoolY(b1, b2_at_t) && IntersektBoolZ(b1, b2_at_t))
				t = t_temp;
		}
		t_temp = (b1.Max.z - b2.Min.z) / v2.z;
		if (t_temp > 0 && t_temp < t)
		{
			b2_at_t = b2.Move(v2 * t_temp);
			if (IntersektBoolY(b1, b2_at_t) && IntersektBoolZ(b1, b2_at_t))
				t = t_temp;
		}
	}

	if (t != FP_INFINITE)
		return (t);
	return (NAN);
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
