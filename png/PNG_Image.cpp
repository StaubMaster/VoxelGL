
#include "PNG_Image.hpp"

PNG_Image::PNG_Image(uint32 w, uint32 h) :
	w(w), h(h)
{
	data = new uint8[w * h * 4];
}
PNG_Image::~PNG_Image()
{
	delete [] data;
}



uint32	PNG_Image::DataIndex(uint32 x, uint32 y)
{
	return ((x + y * w) * 4);
}

void	PNG_Image::setPixelRGBA(uint32 x, uint32 y, uint32 pxl)
{
	uint8 * ptr = (uint8 *)&pxl;
	uint32 idx = DataIndex(x, y);

	data[idx + 0] = ptr[3];
	data[idx + 1] = ptr[2];
	data[idx + 2] = ptr[1];
	data[idx + 3] = ptr[0];
}


PNG_Image * PNG_Image::Scale(uint32 new_w, uint32 new_h)
{
	PNG_Image * img = new PNG_Image(new_w, new_h);

	float scale_x;
	float scale_y;
	uint32	idx_old;
	uint32	idx_new;
	for (uint32 y = 0; y < new_h; y++)
	{
		scale_y = (((float)y) / ((float)new_h)) * ((float)h);

		for (uint32 x = 0; x < new_w; x++)
		{
			scale_x = (((float)x) / ((float)new_w)) * ((float)w);

			idx_old = DataIndex(scale_x, scale_y);
			idx_new = img -> DataIndex(x, y);

			img -> data[idx_new + 0] = data[idx_old + 0];
			img -> data[idx_new + 1] = data[idx_old + 1];
			img -> data[idx_new + 2] = data[idx_old + 2];
			img -> data[idx_new + 3] = data[idx_old + 3];
		}
	}

	return (img);
}

PNG_Image * PNG_Image::Missing()
{
	PNG_Image * img = new PNG_Image(8, 4);

	for (uint32 y = 0; y < 4; y++)
	{
		for (uint32 x = 0; x < 8; x++)
		{
			uint32 pxl;
			if ((x & 1) == (y & 1))
				pxl = 0x000000FF;
			else
				pxl = 0xFF00FFFF;
			img -> setPixelRGBA(x, y, pxl);
		}
	}

	return (img);
}
