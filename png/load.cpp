
#include "PNG.hpp"

const char * PNG_Exception_BadFile::what() const throw() { return "Problem when opening File"; }
const char * PNG_Exception_Signature::what() const throw() { return "Incorrect Signature"; }

std::string	read_whole_file(const std::string & file_path)
{
	std::ifstream file(file_path, std::ios::binary);
	if (!file.is_open())
		throw PNG_Exception_BadFile();

	std::string file_data;
	char	binary_block[1024];

	file.read(binary_block, 1024);
	while (!file.eof())
	{
		file_data += std::string(binary_block, 1024);
		file.read(binary_block, 1024);
	}
	file_data += std::string(binary_block, file.gcount());

	return (file_data);
}




IHDR	load_IHDR(BitStream & bits)
{
	IHDR	ihdr;

	ihdr.width = bits.byte32(BITSTREAM_REV);
	ihdr.height = bits.byte32(BITSTREAM_REV);

	ihdr.bit_depth = bits.byte8();
	ihdr.color_type = bits.byte8();

	ihdr.compression_method = bits.byte8();
	ihdr.filter_method = bits.byte8();
	ihdr.interlace_method = bits.byte8();

	std::cout << " width: " << ihdr.width << "\n";
	std::cout << "height: " << ihdr.height << "\n";

	std::cout << " bit_depth: " << (uint16)ihdr.bit_depth << "\n";
	std::cout << "color_type: " << (uint16)ihdr.color_type << "\n";

	std::cout << "compression_method: " << (uint16)ihdr.compression_method << "\n";
	std::cout << "     filter_method: " << (uint16)ihdr.filter_method << "\n";
	std::cout << "  interlace_method: " << (uint16)ihdr.interlace_method << "\n";

	return (ihdr);
}
void	load_IDAT(BitStream & bits, DataStream & data)
{
	data.Concatenation(bits.Data, bits.Len);
}

void	zlib_decompress(BitStream & bits, DataStream & data)
{
	std::cout << "\e[34mzlib ...\e[m\n";

	ZLIB zlib(bits);
	zlib.ToString();
	std::cout << "\n";

	BitStream deflate = zlib.ToBitStream();
	DEFLATE::Blocks(deflate, data);

	std::cout << "\e[34mzlib done\e[m\n";
}

PNG_Image *	load_png_better(const std::string & file_path)
{
	try
	{
		std::cout << "loading '" << file_path << "' ...\n";
		std::string file_str = read_whole_file(file_path);

		std::cout << "file length: " << file_str.size() << "\n";
		BitStream file(file_str);

		std::cout << "\n";
		{
			uint64	signature_template = 0x0A1A0A0D474E5089;
			uint64	signature_received;

			signature_received = file.byte64();
			std::cout << "signature\n";
			std::cout << "template: " << uint_Hex(signature_template) << "\n";
			std::cout << "received: " << uint_Hex(signature_received) << "\n";

			if (signature_received != signature_template)
				throw PNG_Exception_Signature();
		}
		std::cout << "\n";

		IHDR ihdr;
		DataStream chunk_data(0);

		while (1)
		{
			std::cout << "\n";
			Chunk chunk(file);
			BitStream chunk_stream = chunk.ToBitStream();
			std::cout << chunk.ToString();
			std::cout << "\n";
			if (chunk.isIHRD())
			{
				ihdr = load_IHDR(chunk_stream);
			}
			if (chunk.isIDAT())
			{
				load_IDAT(chunk_stream, chunk_data);
			}
			if (chunk.isIEND())
				break;
		}
	
		BitStream bits(chunk_data.Data, chunk_data.Len);

		DataStream * data = new DataStream(0xFFFFFFFF);
		zlib_decompress(bits, *data);

		PNG_Image * img = new PNG_Image(ihdr.width, ihdr.height);
		PNG_Filter::filter(*data, *img);
		delete data;

		return (img);
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception while loading Image: " << e.what() << "\n";
		return (PNG_Image::Missing());
	}

}
