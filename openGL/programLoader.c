
#include "programLoader.h"

int	load_shader_file(const char *name, GLenum type)
{
	int sh_ID;
	sh_ID = glCreateShader(type);

	char *shader_str;
	const char *shader_const;
	int shader_len;

	shader_str = read_whole_file(name, &shader_len);
	if (shader_str == NULL)
	{
		return (-1);
	}
	shader_const = shader_str;
	glShaderSource(sh_ID, 1, &shader_const, &shader_len);
	free(shader_str);
	glCompileShader(sh_ID);

	char log_txt[1024];
	int log_len;
	glGetShaderInfoLog(sh_ID, 1024, &log_len, log_txt);
	if (log_len != 0)
	{
		int len = 0;
		while (name[len] != '\0')
			len++;
		write(2, "\n", 1);
		write(2, name, len);
		write(2, ":\n", 2);
		write(2, log_txt, log_len);
		write(2, "\n", 1);
	}

	return (sh_ID);
}

int	load_shader_program_VF(const char *vert, const char *frag)
{
	int vert_ID, frag_ID;
	vert_ID = load_shader_file(vert, GL_VERTEX_SHADER);
	frag_ID = load_shader_file(frag, GL_FRAGMENT_SHADER);

	if (vert_ID == -1 || frag_ID == -1)
	{
		glDeleteShader(vert_ID);
		glDeleteShader(frag_ID);
		return (-1);
	}

	int Prog_ID;
	Prog_ID = glCreateProgram();

	glAttachShader(Prog_ID, vert_ID);
	glAttachShader(Prog_ID, frag_ID);
	glLinkProgram(Prog_ID);
	glDetachShader(Prog_ID, vert_ID);
	glDetachShader(Prog_ID, frag_ID);

	glDeleteShader(vert_ID);
	glDeleteShader(frag_ID);

	char log_txt[1024];
	int log_len;
	glGetProgramInfoLog(Prog_ID, 1024, &log_len, log_txt);
	if (log_len != 0)
	{
		glDeleteProgram(Prog_ID);
		write(2, "\nprog:\n", 7);
		write(2, log_txt, log_len);
		write(2, "\n", 1);
		return (-1);
	}

	return (Prog_ID);
}

int	load_shader_programVGF(const char *vert, const char *geom, const char *frag)
{
	int vert_ID, geom_ID, frag_ID;
	vert_ID = load_shader_file(vert, GL_VERTEX_SHADER);
	geom_ID = load_shader_file(geom, GL_GEOMETRY_SHADER);
	frag_ID = load_shader_file(frag, GL_FRAGMENT_SHADER);

	if (vert_ID == -1 || geom_ID == -1 || frag_ID == -1)
	{
		glDeleteShader(vert_ID);
		glDeleteShader(geom_ID);
		glDeleteShader(frag_ID);
		return (-1);
	}

	int Prog_ID;
	Prog_ID = glCreateProgram();

	glAttachShader(Prog_ID, vert_ID);
	glAttachShader(Prog_ID, geom_ID);
	glAttachShader(Prog_ID, frag_ID);
	glLinkProgram(Prog_ID);
	glDetachShader(Prog_ID, vert_ID);
	glDetachShader(Prog_ID, geom_ID);
	glDetachShader(Prog_ID, frag_ID);

	glDeleteShader(vert_ID);
	glDeleteShader(geom_ID);
	glDeleteShader(frag_ID);

	char log_txt[1024];
	int log_len;
	glGetProgramInfoLog(Prog_ID, 1024, &log_len, log_txt);
	if (log_len != 0)
	{
		glDeleteProgram(Prog_ID);
		write(2, "\nprog:\n", 7);
		write(2, log_txt, log_len);
		write(2, "\n", 1);
		return (-1);
	}

	return (Prog_ID);
}
