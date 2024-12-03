
#pragma once

#include "../../openGL.h"

struct BufferCharacterVertex
{
	float	pos_x;
	float	pos_y;
	float	pos_z;
	float	tex_x;
	float	tex_y;

	BufferCharacterVertex();
	BufferCharacterVertex(float pX, float pY, float tX, float tY);
};

struct BufferCharacterSquare
{
	BufferCharacterVertex	V0;
	BufferCharacterVertex	V1;
	BufferCharacterVertex	V2;
	BufferCharacterVertex	V3;
	BufferCharacterVertex	V4;
	BufferCharacterVertex	V5;

	BufferCharacterSquare();
	BufferCharacterSquare(float pX, float pY, float size, float tX, float tY);
};

struct BufferString
{
	unsigned int	Buffer_Array;
	unsigned int	Buffer_Data;

	BufferCharacterSquare	*	Data;
	unsigned int				Len;

	BufferString();
	~BufferString();

	void	Clear();
	void	Append(float pX, float pY, float size, const char * str);

	void	UpdateBuffer();
	void	Draw();
};

#include "Control.hpp"

class TextControl : public Control
{
	private:
		const char *	str;
		float			str_size;

	public:
		TextControl();
		TextControl(Box2D box);
		~TextControl();

		void	UpdateHover(Point2D Mouse);

		void	UpdateRender();

		void	UpdateText(BufferString & buffer, const char * str);
};
