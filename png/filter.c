
#include "png.h"

static uint32_t	pixel_Idx(uint32_t col, uint32_t x, uint32_t y, image *img)
{
	return (col + (x + (y * (img -> w))) * 3);
}
static uint8_t	pixel_X(uint32_t col, uint32_t x, uint32_t y, image *img)
{
	if (x == 0)
		return (0);
	return (img -> data[pixel_Idx(col, x - 1, y, img)]);
}
static uint8_t	pixel_Y(uint32_t col, uint32_t x, uint32_t y, image *img)
{
	if (y == 0)
		return (0);
	return (img -> data[pixel_Idx(col, x, y - 1, img)]);
}

void	filter_None(uint8_t byte, uint32_t col, uint32_t x, uint32_t y, image *img)
{
	img -> data[pixel_Idx(col, x, y, img)] = byte;
}

void	filter_Sub(uint8_t byte, uint32_t col, uint32_t x, uint32_t y, image *img)
{
	uint8_t	a;
	a = pixel_X(col, x, y, img);
	img -> data[pixel_Idx(col, x, y, img)] = byte + a;
}

void	filter_Up(uint8_t byte, uint32_t col, uint32_t x, uint32_t y, image *img)
{
	uint8_t	b;
	b = pixel_Y(col, x, y, img);
	img -> data[pixel_Idx(col, x, y, img)] = byte + b;
}

void	filter_Avg(uint8_t byte, uint32_t col, uint32_t x, uint32_t y, image *img)
{
	uint8_t	a;
	uint8_t	b;
	a = pixel_X(col, x, y, img);
	b = pixel_Y(col, x, y, img);
	img -> data[pixel_Idx(col, x, y, img)] = byte + ((a + b) >> 1);
}

void	filter_Paeth(uint8_t byte, uint32_t col, uint32_t x, uint32_t y, image *img)
{
	uint8_t	a;
	uint8_t	b;
	uint8_t	c;
	a = pixel_X(col, x, y, img);
	b = pixel_Y(col, x, y, img);
	if (x != 0 && y != 0)
		c = img -> data[pixel_Idx(col, x - 1, y - 1, img)];
	else
		c = 0;
	int p = (a + b) - c;
	int diff_a = abs(p - a);
	int diff_b = abs(p - b);
	int diff_c = abs(p - c);

	uint32_t	i = pixel_Idx(col, x, y, img);
	if (diff_a <= diff_b && diff_a <= diff_c)
		img -> data[i] = byte + a;
	else if (diff_b <= diff_c)
		img -> data[i] = byte + b;
	else
		img -> data[i] = byte + c;
}

void	filter(data_block decompressed, image *img)
{
	uint32_t i;
	uint32_t y, x;
	uint8_t byte;
	void (*filter)(uint8_t, uint32_t, uint32_t, uint32_t, image *);

	uint32_t	stride = (img -> w) * 3;
	uint8_t	*row;
	uint8_t	*working;
	row = decompressed.data;

	uint32_t	x_len = (img -> w) * 3;

	i = 0;
	y = 0;
	while (y < (img -> h))
	{
		byte = decompressed.data[i];
		if (byte == 0)
			filter = &filter_None;
		else if (byte == 1)
			filter = &filter_Sub;
		else if (byte == 2)
			filter = &filter_Up;
		else if (byte == 3)
			filter = &filter_Avg;
		else if (byte == 4)
			filter = &filter_Paeth;
		else
			printf("invalid filter %u\n", byte);

		i++;
		x = 0;
		while (x < (img -> w))
		{
			byte = decompressed.data[i];
			filter(byte, 0, x, y, img);
			i++;
			byte = decompressed.data[i];
			filter(byte, 1, x, y, img);
			i++;
			byte = decompressed.data[i];
			filter(byte, 2, x, y, img);
			i++;
			x++;
		}
		y++;
	}
}
