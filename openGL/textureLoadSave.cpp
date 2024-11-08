
#include "textureLoadSave.h"

static void write_uint(int fd, unsigned int i)
{
	unsigned char bytes[4];
	bytes[0] = (i >> 24) & 0xFF;
	bytes[1] = (i >> 16) & 0xFF;
	bytes[2] = (i >> 8) & 0xFF;
	bytes[3] = (i >> 0) & 0xFF;
	write(fd, bytes, 4);
}

static void read_uint(int fd, unsigned int *i)
{
	unsigned char bytes[4];
	read(fd, bytes, 4);
	(*i) = 0;
	(*i) |= ((unsigned int)bytes[0]) << 24;
	(*i) |= ((unsigned int)bytes[1]) << 16;
	(*i) |= ((unsigned int)bytes[2]) << 8;
	(*i) |= ((unsigned int)bytes[3]);
}

#include <errno.h>
#include <string.h>

void texture_save(const char *name, unsigned int *data, int w, int h)
{
	int fd;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		printf("\terror: couldn't open file \"%s\"\n", name);
		printf("\tstrerr: %s\n", strerror(errno));
		return;
	}
	//write(fd, "TEXT-URE", 8);
	write_uint(fd, 0x54455854);
	write_uint(fd, 0x2D555245);
	write_uint(fd, w);
	write_uint(fd, h);

	int size = w * h;
	int i = 0;
	while (i < size)
	{
		write_uint(fd, data[i]);
		i++;
	}

	close(fd);
}

void texture_load(const char *name, unsigned int **data, int *w, int *h)
{
	unsigned int *_data;
	unsigned int _w;
	unsigned int _h;

	(*data) = NULL;

	int fd;
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		printf("\terror: couldn't open file \"%s\"\n", name);
		printf("\tstrerr: %s\n", strerror(errno));
		return;
	}

	// Check Signature and W H
	{
		unsigned int s1, s2;
		read_uint(fd, &s1);
		read_uint(fd, &s2);
		if (!(s1 == 0x54455854 && s2 == 0x2D555245))
		{
			//printf("\twrong signature: %08X%08X != 544558542D555245\n", s1, s2);
			(*data) = NULL;
			printf("\twrong signature\n");
			close(fd);
			return;
		}
		read_uint(fd, &_w);
		read_uint(fd, &_h);
	}

	int size = _w * _h;
	_data = (unsigned int *)calloc(size, sizeof(unsigned int));
	if (_data == NULL)
	{
		printf("\tcouldn't malloc\n");
		close(fd);
		return;
	}

	int i = 0;
	while (i < size)
	{
		read_uint(fd, &(_data[i]));
		i++;
	}

	close(fd);

	(*data) = _data;
	(*w) = _w;
	(*h) = _h;
}