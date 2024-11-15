
#include "png.h"

void	image_header_data(image_header *ihdr)
{
	ihdr -> width = char4_to_uint(&(ihdr -> chunk.data[0]));
	ihdr -> hight = char4_to_uint(&(ihdr -> chunk.data[4]));
	ihdr -> bit_depth = ihdr -> chunk.data[8];
	ihdr -> color_type = ihdr -> chunk.data[9];
	ihdr -> method_compression = ihdr -> chunk.data[10];
	ihdr -> method_filter = ihdr -> chunk.data[11];
	ihdr -> method_interlace = ihdr -> chunk.data[12];

	printf("    Image Header\n");
	printf("width:       %u\n", ihdr -> width);
	printf("hight:       %u\n", ihdr -> hight);
	printf("bit depth:   %u\n", ihdr -> bit_depth);
	printf("color type:  %u\n", ihdr -> color_type);
	printf("compression method: %u\n", ihdr -> method_compression);
	printf("filter      method: %u\n", ihdr -> method_filter);
	printf("interlace   method: %u\n", ihdr -> method_interlace);
}

chunk chunk_read(int fd)
{
	chunk ch;
	ch.length = read_4(fd);
	ch.type = read_4(fd);
	ch.data = malloc(ch.length);
	int ret = read(fd, ch.data, ch.length);
	if (ret <= 0 && ch.length != 0)
	{
		printf("read failed in chunk_read()\n");
		printf("strerror: %s\n", strerror(errno));
		printf("ret: %i\n", ret);
		printf("ch.len: %i\n", ch.length);
	}
	ch.crc = read_4(fd);
	return (ch);
}

void chunk_print(chunk ch)
{
	printf("chunk Length: %u\n", ch.length);

	char *typ = (char *)&ch.type;
	printf("chunk Type:   %c%c%c%c\n",
		typ[3], typ[2], typ[1], typ[0]);
	printf("chunk Type:   %08X\n", ch.type);
	printf("chunk CRC:    %08X\n", ch.crc);
}
