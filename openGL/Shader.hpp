
#ifndef PROGRAMLOADER_HPP
# define PROGRAMLOADER_HPP
# include "openGL.h"
# include "stringHelp.hpp"
# include <iostream>

class Shader
{
	public:
		int	Program_ID;

	public:
		Shader();
		Shader(const std::string vert, const std::string frag);
		Shader(const std::string vert, const std::string geom, const std::string frag);
		~Shader();
	private:
		void operator = (Shader shader);

	public:
		void	Use() const;
		int		FindUniform(const char * uniformName) const;

	private:
		class CompileErrorException : public std::exception { public: const char * what() const throw(); };

	private:
		static int	Load_Shader_File(std::string file, GLenum type);
};

#endif
