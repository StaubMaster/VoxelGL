
#include "png.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("required single file argument\n");
		return (1);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}

	printf("\n");
	{
		uint8_t signature[8];
		read(fd, signature, 8);
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

	image img;

	printf("\n");
	{
		image_header_data(&ihdr);
		img.w = ihdr.width;
		img.h = ihdr.hight;
		img.data = malloc(img.w * img.h * 3);
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

		printf("unfiltered image:\n");
		sixel_draw(decompressed.data, img.w, img.h);
		filter(decompressed, &img);
		free(decompressed.data);
	}
	printf("\n");

	for (uint8_t i = 0; i < chunk_count; i++)
		free(chunk_all[i].data);
	close(fd);

	printf("image:\n");
	sixel_draw(img.data, img.w, img.h);
	free(img.data);
	printf("\n");

	return (0);
}
