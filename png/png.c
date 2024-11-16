
#include "png.h"
#ifndef O_BINARY
# define O_BINARY 0
#endif

image	load_png(const char * name)
{
	image img;
	img.w = 0;
	img.h = 0;
	img.data = NULL;

	int fd = open(name, O_RDONLY | O_BINARY);
	if (fd == -1)
	{
		printf("strerror: %s\n", strerror(errno));
		return (img);
	}
	printf("fd: %i\n", fd);


	printf("\n");
	{
		uint8_t signature[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		int ret = read(fd, signature, 8);
		printf("ret: %i\n", ret);

		printf("PNG Signature (should be equal)\n");
		printf("%02X %02X %02X %02X    %02X %02X %02X %02X\n",
			0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A);
		printf("%02X %02X %02X %02X    %02X %02X %02X %02X\n",
			signature[0], signature[1], signature[2], signature[3],
			signature[4], signature[5], signature[6], signature[7]);
	}
	printf("\n");

	chunk	chunk_curr;
	chunk	chunk_all[16];
	uint8_t	chunk_count = 0;

	while (chunk_count < 16)
	{
		chunk_curr = chunk_read(fd);
		chunk_print(chunk_curr);
		printf("\n");

		chunk_all[chunk_count] = chunk_curr;
		chunk_count++;

		if (chunk_curr.type == 0x49454E44)
		{
			printf("IEND chunk found\n");
			break;
		}
	}

	image_header ihdr;
	image_data idat;

	for (uint8_t i = 0; i < chunk_count; i++)
	{
		if (chunk_all[i].type == 0x49484452)
		{
			ihdr.chunk = chunk_all[i];
			printf("IHDR chunk found\n");
		}
		if (chunk_all[i].type == 0x49444154)
		{
			idat.chunk = chunk_all[i];
			printf("IDAT chunk found\n");
		}
	}

	printf("\n");
	{
		image_header_data(&ihdr);
		img.w = ihdr.width;
		img.h = ihdr.hight;
		img.data = (uint8_t *)malloc(img.w * img.h * 4);
	}
	printf("\n");
	{
		printf("\n    Image Data\n");

		zlib_block	zlib;
		zlib.cmf = idat.chunk.data[0];
		zlib.extra_flags = idat.chunk.data[1];
		zlib.data = &(idat.chunk.data[2]);
		zlib.check_value = idat.chunk.data[idat.chunk.length - 2];

		data_block bit_data;
		bit_data.index = 0;
		bit_data.data = zlib.data;

		data_block decompressed;
		decompressed = decompress_all_blocks(&bit_data);

		filter(decompressed, &img);
		free(decompressed.data);
	}
	printf("\n");

	for (uint8_t i = 0; i < chunk_count; i++)
		free(chunk_all[i].data);
	close(fd);

	/*printf("\n");
	for (uint32_t y = 0; y < img.h; y += 4)
	{
		for (uint32_t x = 0; x < img.w; x += 4)
		{
			uint8_t r = 0, g = 0, b = 0;
			r = img.data[((x + y * img.w) * 4) + 0];
			g = img.data[((x + y * img.w) * 4) + 1];
			b = img.data[((x + y * img.w) * 4) + 2];

			printf("\e[38;2;%i;%i;%im##\e[m", r, g, b);
			//printf("\e[38;2;%i;%i;%im██\e[m", r, g, b);
			//printf("##");
		}
		printf("\n");
	}
	printf("\n");*/

	return (img);
}
