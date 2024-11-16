
#include "_png.h"
#ifndef O_BINARY
# define O_BINARY 0
#endif

void	decode_idat(chunk chunk, data_block * all)
{
			printf("\n    Image Data\n");

			printf("zlib\n");
			zlib_block	zlib;
			zlib.cmf = chunk.data[0];
			zlib.extra_flags = chunk.data[1];

			uint32_t	data_offset = 2;
			uint32_t	dictid = 0;
			uint32_t	adler32 = 0;
			char	bits[33];
			{
				uint8_t cmf, cm, cinfo;
				cmf = zlib.cmf;
				cm = (cmf >> 0) & 0b1111;
				cinfo = (cmf >> 4) & 0b1111;

				uint8_t flg, fcheck, fdict, flevel;
				flg = zlib.extra_flags;
				fcheck = (flg >> 0) & 0b11111;
				fdict = (flg >> 5) & 0b1;
				flevel = (flg >> 6) & 0b11;

				printf("cmf\n");
				printf("  cmf    : %s\n", bits_str(cmf, bits, 7));
				printf("  cm     : %s\n", bits_str(cm, bits, 3));
				printf("  cinfo  : %s\n", bits_str(cinfo, bits, 3));
				if (cm == 8)
					printf("cm == 8: deflate\n");
				printf("\n");

				printf("flg\n");
				printf("  flg    : %s\n", bits_str(flg, bits, 7));
				printf("  fcheck : %s\n", bits_str(fcheck, bits, 3));
				printf("  fdict  : %s\n", bits_str(fdict, bits, 0));
				printf("  flevel : %s\n", bits_str(flevel, bits, 1));
				printf("\n");

				if (fdict != 0)
				{
					dictid = *(uint32_t *)(&chunk.data[2]);
					adler32 = *(uint32_t *)(&chunk.data[chunk.length - 6]);
					data_offset += 4;

					printf("dict\n");
					printf("  dictid  : %08X (%s)\n", dictid, bits_str(dictid, bits, 31));
					printf("  adler32 : %08X (%s)\n", adler32, bits_str(adler32, bits, 31));
					printf("\n");
				}
			}
			(void)adler32;

			zlib.data = &chunk.data[data_offset];
			zlib.check_value = *(uint16_t *)(&chunk.data[chunk.length - 2]);

			data_block bit_data;
			bit_data.index = 0;
			bit_data.data = zlib.data;

			printf("decompress blocks ...\n");
			data_block decompressed;
			decompressed = decompress_all_blocks(&bit_data);
			printf("decompress blocks done: %u\n", decompressed.index);

			if (decompressed.index + all -> index < all -> index)
			{
				printf("Overflow: too much Data\n");
				printf("decompress\n");
			}
			for (uint32_t i = 0; i < decompressed.index; i++)
			{
				all -> data[all -> index] = decompressed.data[i];
				all -> index++;
			}
			free(decompressed.data);
}

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

	data_block decompressed_all;
	decompressed_all.data = (uint8_t *)malloc(0xFFFFFFFF);
	decompressed_all.index = 0;

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

			decode_idat(idat.chunk, &decompressed_all);
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
		printf("filter\n");
		filter(decompressed_all, &img);
		free(decompressed_all.data);
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
