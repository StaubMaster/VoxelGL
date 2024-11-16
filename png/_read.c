
#include "_png.h"

unsigned int char4_to_uint(unsigned char *val)
{
	unsigned int num;
	num = 0;
	num = (num << 8) | val[0];
	num = (num << 8) | val[1];
	num = (num << 8) | val[2];
	num = (num << 8) | val[3];
	return (num);
}

unsigned int read_4(int fd)
{
	unsigned char val[4] = { 0, 0, 0, 0 };
	int ret = read(fd, val, 4);
	if (ret <= 0)
	{
		printf("read failed in read_4()\n");
		printf("strerror: %s\n", strerror(errno));
		printf("ret: %i\n", ret);
	}
	return (char4_to_uint(val));
}
