
#include "Shader.hpp"

Shader::Shader(const std::string name) : Name(name)
{
	std::cout << "++++ Shader '" << Name << "'\n";
	Program_ID = -1;
//	std::cout << Program_ID << "\n";
}
Shader::Shader(const std::string name, const std::string vert, const std::string frag) : Name(name)
{
	std::cout << "++++ Shader VF '" << Name << "'\n";

	int vert_ID, frag_ID;
	vert_ID = Load_Shader_File(vert, GL_VERTEX_SHADER);
	frag_ID = Load_Shader_File(frag, GL_FRAGMENT_SHADER);

	if (vert_ID == -1 || frag_ID == -1)
	{
		glDeleteShader(vert_ID);
		glDeleteShader(frag_ID);
		Program_ID = -1;
		throw CompileErrorException();
	}

	Program_ID = glCreateProgram();

	glAttachShader(Program_ID, vert_ID);
	glAttachShader(Program_ID, frag_ID);
	glLinkProgram(Program_ID);
	glDetachShader(Program_ID, vert_ID);
	glDetachShader(Program_ID, frag_ID);

	glDeleteShader(vert_ID);
	glDeleteShader(frag_ID);

	char log_txt[1024];
	int log_len;
	glGetProgramInfoLog(Program_ID, 1024, &log_len, log_txt);
	if (log_len != 0)
	{
		glDeleteProgram(Program_ID);
		std::cout << "Shader:\n" << std::string(log_txt, log_len) << "\n";
		Program_ID = -1;
		throw CompileErrorException();
	}

//	std::cout << Program_ID << "\n";
}
Shader::Shader(const std::string name, const std::string vert, const std::string geom, const std::string frag) : Name(name)
{
	std::cout << "++++ Shader VGF '" << Name << "'\n";

	int vert_ID, geom_ID, frag_ID;
	vert_ID = Load_Shader_File(vert, GL_VERTEX_SHADER);
	geom_ID = Load_Shader_File(geom, GL_GEOMETRY_SHADER);
	frag_ID = Load_Shader_File(frag, GL_FRAGMENT_SHADER);

	if (vert_ID == -1 || geom_ID == -1 || frag_ID == -1)
	{
		glDeleteShader(vert_ID);
		glDeleteShader(geom_ID);
		glDeleteShader(frag_ID);
		Program_ID = -1;
		throw CompileErrorException();
	}

	Program_ID = glCreateProgram();

	glAttachShader(Program_ID, vert_ID);
	glAttachShader(Program_ID, geom_ID);
	glAttachShader(Program_ID, frag_ID);
	glLinkProgram(Program_ID);
	glDetachShader(Program_ID, vert_ID);
	glDetachShader(Program_ID, geom_ID);
	glDetachShader(Program_ID, frag_ID);

	glDeleteShader(vert_ID);
	glDeleteShader(geom_ID);
	glDeleteShader(frag_ID);

	char log_txt[1024];
	int log_len;
	glGetProgramInfoLog(Program_ID, 1024, &log_len, log_txt);
	if (log_len != 0)
	{
		glDeleteProgram(Program_ID);
		std::cout << "Shader:\n" << std::string(log_txt, log_len) << "\n";
		Program_ID = -1;
		throw CompileErrorException();
	}

//	std::cout << Program_ID << "\n";
}
Shader::~Shader()
{
	std::cout << "---- Shader '" << Name << "'\n";
	glDeleteProgram(Program_ID);
//	std::cout << Program_ID << "\n";
}

void	Shader::Use() const
{
//	std::cout << "Use() Shader\n";
	glUseProgram(Program_ID);
//	std::cout << Program_ID << "\n";
}
int		Shader::FindUniform(const char * uniformName) const
{
	return glGetUniformLocation(Program_ID, uniformName);
}


const char * Shader::CompileErrorException::what() const throw() { return " Error while compiling Shader Program"; }



int	Shader::Load_Shader_File(std::string file, GLenum type)
{
	int sh_ID;
	sh_ID = glCreateShader(type);

	std::string shader_str;
	shader_str = read_whole_file(file);

	const char * shader_txt = shader_str.c_str();
	int	shader_len = shader_str.size();

	glShaderSource(sh_ID, 1, &shader_txt, &shader_len);
	glCompileShader(sh_ID);

	char log_txt[1024];
	int log_len;
	glGetShaderInfoLog(sh_ID, 1024, &log_len, log_txt);
	if (log_len != 0)
	{
		std::cout << file << ":\n" << std::string(log_txt, log_len) << "\n";
	}

	return (sh_ID);
}
