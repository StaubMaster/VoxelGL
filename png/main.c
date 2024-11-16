
#include "png.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("required single file argument\n");
		return (1);
	}

	image img = load_png(argv[1]);

	printf("image:\n");
	sixel_draw(img.data, img.w, img.h);
	free(img.data);
	printf("\n");

	return (0);
}
