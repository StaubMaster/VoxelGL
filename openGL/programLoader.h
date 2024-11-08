
#ifndef PROGRAMLOADER_H
# define PROGRAMLOADER_H
# include "openGL.h"
# include "stringHelp.h"

int	load_shader_file(const char *name, GLenum type);
int	load_shader_program_VF(const char *vert, const char *frag);
int	load_shader_programVGF(const char *vert, const char *geom, const char *frag);

#endif
