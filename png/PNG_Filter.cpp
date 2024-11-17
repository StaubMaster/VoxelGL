
#include "PNG_Filter.hpp"

PNG_Filter::PixelData::PixelData(PNG_Image & img) :
	img(img)
{
	
}

uint32	PNG_Filter::PixelIndex(PixelData pxl)
{
	return (((pxl.img.w * pxl.y + pxl.x) * 4) + pxl.col);
}

uint8	PNG_Filter::getPixel(PixelData pxl, uint8 rel)
{
	if ((rel & rel_X) != 0)
	{
		if (pxl.x == 0)
			return (0);
		pxl.x--;
	}

	if ((rel & rel_Y) != 0)
	{
		if (pxl.y == 0)
			return (0);
		pxl.y--;
	}

	return (pxl.img.data[PixelIndex(pxl)]);
}

void	PNG_Filter::filter_None(PixelData pxl, uint8 byte)
{
	pxl.img.data[PixelIndex(pxl)] = byte;
}
void	PNG_Filter::filter_Sub(PixelData pxl, uint8 byte)
{
	uint8	a = getPixel(pxl, rel_X);
	pxl.img.data[PixelIndex(pxl)] = byte + a;
}
void	PNG_Filter::filter_Up(PixelData pxl, uint8 byte)
{
	uint8	b = getPixel(pxl, rel_Y);
	pxl.img.data[PixelIndex(pxl)] = byte + b;
}
void	PNG_Filter::filter_Avg(PixelData pxl, uint8 byte)
{
	uint8	a = getPixel(pxl, rel_X);
	uint8	b = getPixel(pxl, rel_Y);
	pxl.img.data[PixelIndex(pxl)] = byte + ((a + b) >> 1);
}
void	PNG_Filter::filter_Paeth(PixelData pxl, uint8 byte)
{
	uint8	a = getPixel(pxl, rel_X);
	uint8	b = getPixel(pxl, rel_Y);
	uint8	c = getPixel(pxl, rel_XY);

	int	p = (a + b) - c;
	int diff_a = abs(p - a);
	int diff_b = abs(p - b);
	int diff_c = abs(p - c);

	if (diff_a <= diff_b && diff_a <= diff_c)
		pxl.img.data[PixelIndex(pxl)] = byte + a;
	else if (diff_b <= diff_c)
		pxl.img.data[PixelIndex(pxl)] = byte + b;
	else
		pxl.img.data[PixelIndex(pxl)] = byte + c;
}

void	PNG_Filter::filter(DataStream & data, PNG_Image & img)
{
	PixelData pxl(img);
	void (*filter)(PixelData, uint8);

	data.Index = 0;

	uint8	data_byte;
	for (pxl.y = 0; pxl.y < img.h; pxl.y++)
	{
		data_byte = data.Exsert();
		if (data_byte == 0)
			filter = &filter_None;
		else if (data_byte == 1)
			filter = &filter_Sub;
		else if (data_byte == 2)
			filter = &filter_Up;
		else if (data_byte == 3)
			filter = &filter_Avg;
		else if (data_byte == 4)
			filter = &filter_Paeth;

		for (pxl.x = 0; pxl.x < img.w; pxl.x++)
		{
			data_byte = data.Exsert();
			pxl.col = 0;
			filter(pxl, data_byte);

			data_byte = data.Exsert();
			pxl.col = 1;
			filter(pxl, data_byte);

			data_byte = data.Exsert();
			pxl.col = 2;
			filter(pxl, data_byte);

			pxl.col = 3;
			img.data[PixelIndex(pxl)] = 0xFF;
		}
	}
}
