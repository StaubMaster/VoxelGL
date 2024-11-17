
#ifndef PNG_HPP
# define PNG_HPP
# include <fstream>
# include <iostream>

# include "uint.hpp"
# include "BitStream.hpp"
# include "Chunk.hpp"

struct IHDR
{
	uint32	width;
	uint32	height;

	uint8	bit_depth;
	uint8	color_type;

	uint8	compression_method;
	uint8	filter_method;
	uint8	interlace_method;
};

IHDR	load_IHDR(BitStream & bits);

void	load_png_better(const std::string & file_path);

#endif
