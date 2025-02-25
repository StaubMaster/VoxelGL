
#ifndef STRINGHELP_H
# define STRINGHELP_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <fstream>

int str_len(const char *name);
int copy_add_free(char **arr_data, int *arr_len, char *buf, int siz);
char * read_whole_file(const char *name, int *len);
std::string read_whole_file(std::string path);

#endif
