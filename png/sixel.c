
#include "png.h"

static int	char_itoa_len(char n)
{
	if (n < 0)
		return (0);
	if (n < 10)
		return (1);
	if (n < 100)
		return (2);
	return (3);
}

static void	set_color(char col, unsigned char r, unsigned char g, unsigned char b)
{
	r = (r * 100) / 255;
	g = (g * 100) / 255;
	b = (b * 100) / 255;

	char	len[4];
	len[0] = char_itoa_len(col);
	len[1] = char_itoa_len(r);
	len[2] = char_itoa_len(g);
	len[3] = char_itoa_len(b);

	char	len_sum;
	len_sum = 6;
	len_sum += len[0];
	len_sum += len[1];
	len_sum += len[2];
	len_sum += len[3];

	char	*str;
	str = (char *)calloc(len_sum, sizeof(char));
	int	idx;

	idx = -1;
	str[++idx] = '#';
	if (len[0] == 3) {	str[++idx] = (col / 100) + '0';		len[0]--;	}
	if (len[0] == 2) {	str[++idx] = (col / 10) % 10 + '0';	len[0]--;	}
	if (len[0] == 1) {	str[++idx] = (col) % 10 + '0';		len[0]--;	}

	str[++idx] = ';';
	str[++idx] = '2';

	str[++idx] = ';';
	if (len[1] == 3) {	str[++idx] = (r / 100) + '0';		len[1]--;	}
	if (len[1] == 2) {	str[++idx] = (r / 10) % 10 + '0';	len[1]--;	}
	if (len[1] == 1) {	str[++idx] = (r) % 10 + '0';		len[1]--;	}

	str[++idx] = ';';
	if (len[2] == 3) {	str[++idx] = (g / 100) + '0';		len[2]--;	}
	if (len[2] == 2) {	str[++idx] = (g / 10) % 10 + '0';	len[2]--;	}
	if (len[2] == 1) {	str[++idx] = (g) % 10 + '0';		len[2]--;	}

	str[++idx] = ';';
	if (len[3] == 3) {	str[++idx] = (b / 100) + '0';		len[3]--;	}
	if (len[3] == 2) {	str[++idx] = (b / 10) % 10 + '0';	len[3]--;	}
	if (len[3] == 1) {	str[++idx] = (b) % 10 + '0';		len[3]--;	}

	write(1, str, len_sum);
	free(str);
}

void	sixel_draw(uint8_t *data, uint32_t w, uint32_t h)
{
	write(1, "\ePq", 3);

	//int		sixl_idx;
	char	sixl_sft;
	char	sixl;
	int		idx;

	uint32_t	x, y;
	y = 0;
	while (y < h)
	{
		//sixl_idx = y / 6;
		sixl_sft = y % 6;
		x = 0;
		while (x < w)
		{
			idx = (x + y * w) * 4;
			set_color(0, data[idx + 0], data[idx + 1], data[idx + 2]);
			sixl = 1 << sixl_sft;
			sixl += 63;
			write(1, &sixl, 1);
			x++;
		}
		if (sixl_sft < 5)
			write(1, "$", 1);
		else
			write(1, "-", 1);
		y++;
	}

	write(1, "\e\\\n", 3);
}

void	sixel_draw_r(uint8_t *data, uint32_t w, uint32_t h)
{
	write(1, "\ePq", 3);

	//int		sixl_idx;
	char	sixl_sft;
	char	sixl;
	int		idx;

	uint32_t	x, y;
	y = 0;
	while (y < h)
	{
		//sixl_idx = y / 6;
		sixl_sft = y % 6;
		x = 0;
		while (x < w)
		{
			idx = (x + y * w) * 3;
			set_color(0, data[idx + 0], 0, 0);
			sixl = 1 << sixl_sft;
			sixl += 63;
			write(1, &sixl, 1);
			x++;
		}
		if (sixl_sft < 5)
			write(1, "$", 1);
		else
			write(1, "-", 1);
		y++;
	}

	write(1, "\e\\\n", 3);
}

void	sixel_draw_g(uint8_t *data, uint32_t w, uint32_t h)
{
	write(1, "\ePq", 3);

	//int		sixl_idx;
	char	sixl_sft;
	char	sixl;
	int		idx;

	uint32_t	x, y;
	y = 0;
	while (y < h)
	{
		//sixl_idx = y / 6;
		sixl_sft = y % 6;
		x = 0;
		while (x < w)
		{
			idx = (x + y * w) * 3;
			set_color(0, 0, data[idx + 1], 0);
			sixl = 1 << sixl_sft;
			sixl += 63;
			write(1, &sixl, 1);
			x++;
		}
		if (sixl_sft < 5)
			write(1, "$", 1);
		else
			write(1, "-", 1);
		y++;
	}

	write(1, "\e\\\n", 3);
}

void	sixel_draw_b(uint8_t *data, uint32_t w, uint32_t h)
{
	write(1, "\ePq", 3);

	//int		sixl_idx;
	char	sixl_sft;
	char	sixl;
	int		idx;

	uint32_t	x, y;
	y = 0;
	while (y < h)
	{
		//sixl_idx = y / 6;
		sixl_sft = y % 6;
		x = 0;
		while (x < w)
		{
			idx = (x + y * w) * 3;
			set_color(0, 0, 0, data[idx + 2]);
			sixl = 1 << sixl_sft;
			sixl += 63;
			write(1, &sixl, 1);
			x++;
		}
		if (sixl_sft < 5)
			write(1, "$", 1);
		else
			write(1, "-", 1);
		y++;
	}

	write(1, "\e\\\n", 3);
}
