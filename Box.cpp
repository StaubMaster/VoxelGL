
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
	check on which sides b1 is intersekting b2
	being fully inside is not an intersektion
*/
/*
	Y
	|
	#---X
statements are from the # box perspective
+ boxes are voxels

		#-------#
		|		|
	+---|-------|---+
	|	|		|	|
	|	#-------#	|
	|				|
	+---------------+
	this is an Intersektion on the Y side

		#-----------#
		|			|
	+---|-------+	|
	|	|		|	|
	|	#-------|---#
	|			|
	+-----------+
	this is an Intersektion on the Y side and the X side

		#-------#
		|		|
	+---|---+---|---+
	|	|	|	|	|
	|	#-------#	|
	|		|		|
	+-------+-------+
	this is an Intersektion on the Y side and both X sides
	this should be an Intersektion on the Y side only

I neen t 'collect' where something is colliding with something
//if I get a Intersektion on a X side and then the other, they cancel out
or everything together, if anything is double, ignore

	+-------+
	|		|
	|	#-------#
	|	|	|	|
	+---|---+---|---+
		|	|	|	|
		#-------#	|
			|		|
			+-------+
	intersektion on no side
	the stuck mechanic should handle this

	+-------+
	|		|
	|	#-------#
	|	|	|	|
	+---|---+---|---+
	|	|	|	|	|
	|	#-------#	|
	|		|		|
	+-------+-------+
	intersektion on no side
	the stuck mechanic should handle this
*/
char	Box::IntersektBits(const Box & b1, const Box & b2)
{
	char	x_partial = 0;
	char	y_partial = 0;
	char	z_partial = 0;

	char	inter = 0;
	if (b1.Min.x < b2.Max.x) { inter |= AXIS_BIT_XN; x_partial++; }
	if (b1.Max.x > b2.Min.x) { inter |= AXIS_BIT_XP; x_partial++; }
	if (b1.Min.y < b2.Max.y) { inter |= AXIS_BIT_YN; y_partial++; }
	if (b1.Max.y > b2.Min.y) { inter |= AXIS_BIT_YP; y_partial++; }
	if (b1.Min.z < b2.Max.z) { inter |= AXIS_BIT_ZN; z_partial++; }
	if (b1.Max.z > b2.Min.z) { inter |= AXIS_BIT_ZP; z_partial++; }

	//char	x_partial = ((inter & AXIS_BIT_XN) != 0) + ((inter & AXIS_BIT_XP) != 0);
	//char	y_partial = ((inter & AXIS_BIT_YN) != 0) + ((inter & AXIS_BIT_YP) != 0);
	//char	z_partial = ((inter & AXIS_BIT_ZN) != 0) + ((inter & AXIS_BIT_ZP) != 0);

	char	bits = 0;

	if ((x_partial == 1) && (y_partial != 0) && (z_partial != 0))
	{
		if (inter & AXIS_BIT_XN) { bits |= AXIS_BIT_XN; }
		if (inter & AXIS_BIT_XP) { bits |= AXIS_BIT_XP; }
	}
	if ((x_partial != 0) && (y_partial == 1) && (z_partial != 0))
	{
		if (inter & AXIS_BIT_YN) { bits |= AXIS_BIT_YN; }
		if (inter & AXIS_BIT_YP) { bits |= AXIS_BIT_YP; }
	}
	if ((x_partial != 0) && (y_partial != 0) && (z_partial == 1))
	{
		if (inter & AXIS_BIT_ZN) { bits |= AXIS_BIT_ZN; }
		if (inter & AXIS_BIT_ZP) { bits |= AXIS_BIT_ZP; }
	}

	return (bits);
}



/*
	used for pushing 2 boxes apart
	b1 should be the static box
	b2 should be the box that moves
*/
Point	Box::IntersektDiff(const Box & b1, const Box & b2)
{
	if (!IntersektBool(b1, b2))
	{
		return Point();
	}

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
}

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
