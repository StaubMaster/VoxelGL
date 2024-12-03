
#include "Text.hpp"


static void	MapChar(char c, float & tX, float & tY)
{
	if (c >= '0' && c <= '9')
	{
		tX = c - '0';
		tY = 0;
	}
	else if (c >= 'A' && c <= 'M')
	{
		tX = c - 'A';
		tY = 1;
	}
	else if (c >= 'N' && c <= 'Z')
	{
		tX = c - 'N';
		tY = 2;
	}
	else if (c >= 'a' && c <= 'm')
	{
		tX = c - 'a';
		tY = 3;
	}
	else if (c >= 'n' && c <= 'z')
	{
		tX = c - 'n';
		tY = 4;
	}
	else
	{
		tX = 15;
		tY = 7;
	}
}
static bool	SpecialChar(char c, float & pX, float & pY)
{
	if (c == ' ')
	{
		pX++;
		return (true);
	}
	else if (c == '\n')
	{
		pX = 0;
		pY++;
		return (true);
	}
	else
	{
		return (false);
	}
}



BufferCharacterVertex::BufferCharacterVertex() { }
BufferCharacterVertex::BufferCharacterVertex(float pX, float pY, float tX, float tY)
{
	pos_x = pX;
	pos_y = pY;
	pos_z = 0.5f;
	tex_x = tX * 0.0625f;
	tex_y = tY * 0.1250f;
}



BufferCharacterSquare::BufferCharacterSquare() { }
BufferCharacterSquare::BufferCharacterSquare(float pX, float pY, float size, float tX, float tY)
{
	float	min_x = pX;
	float	max_x = pX + size;
	float	min_y = pY;
	float	max_y = pY + size;

	V0 = BufferCharacterVertex(min_x, min_y, tX + 0, tY + 0);
	V1 = BufferCharacterVertex(max_x, min_y, tX + 1, tY + 0);
	V2 = BufferCharacterVertex(min_x, max_y, tX + 0, tY + 1);
	V3 = BufferCharacterVertex(min_x, max_y, tX + 0, tY + 1);
	V4 = BufferCharacterVertex(max_x, min_y, tX + 1, tY + 0);
	V5 = BufferCharacterVertex(max_x, max_y, tX + 1, tY + 1);
}



BufferString::BufferString()
{
	glGenVertexArrays(1, &Buffer_Array);
	glBindVertexArray(Buffer_Array);
	glGenBuffers(1, &Buffer_Data);

	Len = 0;
	Data = new BufferCharacterSquare[Len];
}
BufferString::~BufferString()
{
	glBindVertexArray(Buffer_Array);
	glDeleteBuffers(1, &Buffer_Data);
	glDeleteVertexArrays(1, &Buffer_Array);

	delete [] Data;
}

void	BufferString::Clear()
{
	delete [] Data;

	Len = 0;
	Data = new BufferCharacterSquare[Len];
}
void	BufferString::Append(float pX, float pY, float size, const char * str)
{
	float tX, tY;
	float oX, oY;

	unsigned int len = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (!SpecialChar(str[i], oX, oY))
			len++;
	}

	BufferCharacterSquare * data = new BufferCharacterSquare[Len + len];
	for (unsigned int i = 0; i < Len; i++)
		data[i] = Data[i];
	delete [] Data;
	Data = data;

	oX = 0;
	oY = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (!SpecialChar(str[i], oX, oY))
		{
			MapChar(str[i], tX, tY);
			Data[Len] = BufferCharacterSquare(pX + oX * size, pY + oY * (size * 1.1f), size, tX, tY);
			Len++;
			oX++;
		}
	}
}
void	BufferString::UpdateBuffer()
{
	glBindVertexArray(Buffer_Array);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer_Data);
	glBufferData(GL_ARRAY_BUFFER, Len * sizeof(float) * 5 * 6, Data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, (void *)(sizeof(float) * 0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 5, (void *)(sizeof(float) * 3));
}
void	BufferString::Draw()
{
	glBindVertexArray(Buffer_Array);
	glDrawArrays(GL_TRIANGLES, 0, Len * 5 * 6);
}





TextControl::TextControl() :
	Control()
{

}
TextControl::TextControl(Box2D box) :
	Control(box)
{

}
TextControl::~TextControl()
{

}



void	TextControl::UpdateHover(Point2D Mouse)
{
	Control::UpdateHover(Mouse);
	UpdateRender();
}



void	TextControl::UpdateRender()
{
	if (render == NULL)
		return;

	if (!isHover)
	{
		render -> Col.R = 1.00;
		render -> Col.G = 1.00;
		render -> Col.B = 1.00;
	}
	else
	{
		render -> Col.R = 0.875;
		render -> Col.G = 0.875;
		render -> Col.B = 0.875;
	}

	render -> Depth = 0.75f;
}

void	TextControl::UpdateText(BufferString & buffer, const char * str)
{
	float x, y, size;
	x = Box.Min.X + 12.0f;
	y = Box.Min.Y + 12.0f;
	size = Size.H - 24.0f;
	buffer.Append(x, y, size, str);
}
