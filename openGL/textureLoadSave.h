
#ifndef TEXTURELOADSAVE_H
# define TEXTURELOADSAVE_H
# include "openGL.h"

void texture_save(const char *name, unsigned int *data, int w, int h);
void texture_load(const char *name, unsigned int **data, int *w, int *h);

#endif
