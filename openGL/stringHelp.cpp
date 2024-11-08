
#include "stringHelp.h"

int str_len(const char *name)
{
	if (name == NULL) { return (0); }
	int i = 0;
	while (name[i] != '\0')
		i++;
	return (i);
}

int	copy_add_free(char **arr_data, int *arr_len, char *buf, int siz)
{
	char	*arr_new;
	int		i;

	arr_new = (char *)calloc((*arr_len) + siz, sizeof(char));
	if (arr_new == NULL)
		return (0);
	i = 0;
	while (i < (*arr_len))
	{
		arr_new[i] = (*arr_data)[i];
		i++;
	}
	free((*arr_data));
	i = 0;
	while (i < siz)
	{
		arr_new[(*arr_len) + i] = buf[i];
		i++;
	}
	(*arr_len) += siz;
	(*arr_data) = arr_new;
	return (1);
}

char	*read_whole_file(const char *name, int *len)
{
	int fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		write(2, "\nFile Not Found\n", 16);
		write(2, name, str_len(name));
		write(2, "\n", 1);
		return (NULL);
	}

	char	*arr_data = (char *)calloc(1, sizeof(char));
	if (arr_data == NULL)
	{
		close(fd);
		write(2, "\ncouldn't malloc\n", 17);
		return (NULL);
	}
	int		arr_len = 0;

	char	buf[256];
	int		siz;

	siz = read(fd, buf, 256);
	while (siz == 256)
	{
		if (copy_add_free(&arr_data, &arr_len, buf, 256) == 0)
		{
			close(fd);
			free(arr_data);
			write(2, "\ncouldn't malloc\n", 17);
			return (NULL);
		}
		siz = read(fd, buf, 256);
	}
	close(fd);
	if (copy_add_free(&arr_data, &arr_len, buf, siz) == 0)
	{
		close(fd);
		free(arr_data);
		write(2, "\ncouldn't malloc\n", 17);
		return (NULL);
	}
	arr_data[arr_len] = '\0';

	(*len) = arr_len;
	return (arr_data);
}
